import os
import sys

from FilesCollecter import FilesCollecter

#------------------------------------------------------------------------------

is_valid = True

if len(sys.argv) == 2:
	SOURCE_DIR = os.path.abspath(os.path.curdir)
	EXTENSION = sys.argv[1]
elif len(sys.argv == 3):
	SOURCE_DIR = sys.argv[1]
	EXTENSION = sys.argv[2]
else:
	is_valid = False
	print("Invalid params count")

#------------------------------------------------------------------------------

def change_delimiters(files_list):
	result = []
	for file_name in files_list:
		result.append(file_name.replace('\\', '/'))
	return result

if is_valid:
	collecter = FilesCollecter(SOURCE_DIR, EXTENSION)
	result = change_delimiters(collecter.run())
	print(result)

#------------------------------------------------------------------------------
