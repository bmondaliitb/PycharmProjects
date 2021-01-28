import h5py
import tflearn
import numpy as np
from tflearn.data_utils import shuffle
from tflearn.data_utils import to_categorical
from tflearn.layers.core import input_data, dropout, fully_connected
from tflearn.layers.conv import conv_2d, max_pool_2d
from tflearn.layers.estimator import regression

from sklearn import metrics
from sklearn.metrics import roc_curve, auc

import matplotlib.pyplot as plt

from main import *

# Data loading
# Note: You input here any dataset you would like to finetune
# first slicing numpy arrays from the main file to use for train and validation
outputName_signal = "tty_prod_event_images.h5"
outputName_background = "tty_dec_event_images.h5"

# For signal
with h5py.File(outputName_signal, 'r') as hdf:
    data_signal = hdf.get('1')
    dataset_signal = np.array(data_signal)

X = dataset_signal.reshape(-1, 80, 80, 1)

#np.set_printoptions(threshold=np.inf)
#print(X[0])

# For background
with h5py.File(outputName_background, 'r') as hdf:
    data_background = hdf.get('1')
    dataset_background = np.array(data_background)

X_1 = dataset_background.reshape(-1, 80, 80, 1)

# labels
signal_label = np.array([[0, 1]] * len(dataset_signal))
background_label = np.array([[1, 0]] * len(dataset_background))
# background_label = np.concatenate((background_label, background_label_1), axis = 0)

X = np.concatenate((X, X_1), axis=0)
Y = np.concatenate((signal_label, background_label), axis=0)

# To shuffle the data
X, Y = shuffle(X, Y)

# Y = to_categorical(Y)

num_classes = 2
# Redefinition of convnet_cifar10 network
network = input_data(shape=[None, 80, 80, 1])
network = conv_2d(network, 32, 3, activation='relu')
network = max_pool_2d(network, 2)
network = dropout(network, 0.75)
network = conv_2d(network, 64, 3, activation='relu')
network = conv_2d(network, 64, 3, activation='relu')
network = max_pool_2d(network, 2)
network = dropout(network, 0.5)
network = fully_connected(network, 512, activation='relu')
network = dropout(network, 0.5)
# Finetuning Softmax layer (Setting restore=False to not restore its weights)
softmax = fully_connected(network, num_classes, activation='softmax', restore=False)
regression = regression(softmax, optimizer='adam',
                        loss='categorical_crossentropy',
                        learning_rate=0.01)

model = tflearn.DNN(regression, checkpoint_path='model_finetuning',
                    max_checkpoints=3, tensorboard_verbose=0)
# Load pre-existing model, restoring all weights, except softmax layer ones
#model.load('cifar10_cnn')

#Start finetuning
model.fit(X, Y, n_epoch=100, validation_set=0.15, shuffle=True,
          show_metric=True, batch_size=64, snapshot_step=200,
          snapshot_epoch=False, run_id='model_finetuning')

model.save('model_finetuning_epoch_10')

#########################Save the model for 100 epochs, then load it and do the calculations####################
#model.load('model_finetuning_epoch_100')
#
#Y_score = np.array([])
#for i in range(len(X)):
#    score = model.predict([X[i]])
#    Y_score = np.append(Y_score, score[:,1])
#
## Y_score = Y_score[:, 1]
#Y= Y[:, 1]
#
#fpr, tpr, thresholds = metrics.roc_curve(Y, Y_score)
#
#roc_auc = auc(fpr, tpr)
#
######### Drawing the ROC curve #############################
#
#plt.figure()
#lw = 2
#plt.plot(tpr, 1.0-fpr, color='darkorange',
#         lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
#plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
#plt.xlim([0.0, 1.0])
#plt.ylim([0.0, 1.05])
#plt.xlabel('Signal Efficiency')
#plt.ylabel('Background Rejection') #True Positive Rate
#plt.title('Receiver operating characteristic')
#plt.legend(loc="lower right")
#plt.show()

