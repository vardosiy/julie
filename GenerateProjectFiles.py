import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from FilterData import FilterData
from FilesListsGenerator import FilesListsGenerator

#------------------------------------------------------------------------------

filters = list()
filters.append(FilterData("sources",	[".c", ".cpp", ".inl"]))
filters.append(FilterData("headers",	[".h", ".hpp"]))
filters.append(FilterData("resources",	[".qrc"]))
filters.append(FilterData("ui_sources",	[".ui"]))
filters.append(FilterData("shaders",	[".vs", ".fs"]))

targets_dirs = list()
targets_dirs.append("3rd-party/glad")
targets_dirs.append("src/app")
targets_dirs.append("src/julie")
targets_dirs.append("src/utils")
targets_dirs.append("src/tests/utils_tests")

output_file_name = "Autogen.cmake"
build_dir = "build"

#------------------------------------------------------------------------------

def generate_files_lists(filters, targets_dirs, output_file_name):
	generator = FilesListsGenerator(filters)
	for target_dir in targets_dirs:
		print(f"[INFO] Generating files list for {target_dir}")
		generator.generate_files_lists(os.path.normpath(target_dir), output_file_name)

#------------------------------------------------------------------------------

def generate_prj_files(build_dir):
	if not os.path.exists(build_dir):
		os.mkdir(build_dir)

	os.chdir(build_dir)
	os.system("cmake ..")

#------------------------------------------------------------------------------

generate_files_lists(filters, targets_dirs, output_file_name)
#generate_prj_files(build_dir)

#------------------------------------------------------------------------------
