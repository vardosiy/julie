import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from FilterData import FilterData
from FilesListsGenerator import FilesListsGenerator

#------------------------------------------------------------------------------

filters = [
	FilterData("sources",		[".c", ".cpp", ".inl"]	),
	FilterData("headers",		[".h", ".hpp"]			),
	FilterData("resources",		[".qrc"]				),
	FilterData("ui_sources",	[".ui"]					),
	FilterData("shaders",		[".vs", ".fs"]			),
]

targets_dirs = [
	"3rd-party/glad",
	"src/app",
	"src/julie",
	"src/utils",
	"src/tests/utils_tests",
]

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
generate_prj_files(build_dir)

#------------------------------------------------------------------------------
