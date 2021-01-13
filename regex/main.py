# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('PyCharm')
    import re
    #\.[0 - 9]{6}. *
    s = "mc16a_ttgamma_nominal123456.1.root"
    stringy = 'CPLR_DUK10_772989_2'
    dsid = re.compile("[0-9]{6}.*")
    result = dsid.search(s)
    print(result)
    sample_type = s.replace(result.group(0), '')
    print (sample_type)
