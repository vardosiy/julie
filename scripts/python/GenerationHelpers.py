import os

from FilesListsGenerator import FilesListsGenerator

#------------------------------------------------------------------------------

def generate_files_lists(filters, targets_dirs):
	generator = FilesListsGenerator()

	for filter in filters:
		generator.add_filter(filter)

	for target_dir in targets_dirs:
		generator.generate_files_list(os.path.normpath(target_dir))

#------------------------------------------------------------------------------

def generate_prj_files(build_dir):
	if not os.path.exists(build_dir):
		os.mkdir(build_dir)

	os.chdir(build_dir)
	os.system("cmake ..")

#------------------------------------------------------------------------------
