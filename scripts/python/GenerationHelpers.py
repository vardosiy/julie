import os

from FilesListsGenerator import FilesListsGenerator

#------------------------------------------------------------------------------

def generate_files_lists(filters, targets_dirs, output_file_name):
	generator = FilesListsGenerator()
	generator.set_filters(filters)

	for target_dir in targets_dirs:
		generator.generate_files_lists(os.path.normpath(target_dir), output_file_name)

#------------------------------------------------------------------------------

def generate_prj_files(build_dir):
	if not os.path.exists(build_dir):
		os.mkdir(build_dir)

	os.chdir(build_dir)
	os.system("cmake ..")

#------------------------------------------------------------------------------
