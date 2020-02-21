import os
from string import Template

#------------------------------------------------------------------------------

file_template = """{
	"vs": "
		$vs
	",

	"fs": "
		$fs
	"
}"""

vs_file_extension = ".vs"
fs_file_extension = ".fs"
output_file_extension = ".shdata"
output_folder = "composed"
indent = "\t\t"

#------------------------------------------------------------------------------

def vs_filter_fun(item):
	if os.path.splitext(item)[1] == vs_file_extension:
		return True
	return False

#------------------------------------------------------------------------------

def build_fs_file_name(vs_file_name):
	return os.path.splitext(vs_file_name)[0] + fs_file_extension

#------------------------------------------------------------------------------

def build_output_file_path(vs_file_name):
	file_name = os.path.splitext(vs_file_name)[0] + output_file_extension
	return os.path.join(output_folder, file_name)

#------------------------------------------------------------------------------

def indent_file(file_content):
	return file_content.replace("\n", "\n" + indent)

#------------------------------------------------------------------------------

def compose_shader_files_into_single_file(vs_file_name, fs_file_name, output_file_path):
	vs_file = open(vs_file_name, "r")
	fs_file = open(fs_file_name, "r")

	vs_shader = indent_file(vs_file.read())
	fs_shader = indent_file(fs_file.read())

	output_str = Template(file_template).substitute(vs=vs_shader, fs=fs_shader)
	output_file = open(output_file_path, "w")
	output_file.write(output_str)

#------------------------------------------------------------------------------

dir_content = os.listdir(os.curdir)
vs_files_names = filter(vs_filter_fun, dir_content)

os.mkdir(output_folder)

for vs_file_name in vs_files_names:
	fs_file_name = build_fs_file_name(vs_file_name)
	output_file_name = build_output_file_path(vs_file_name)
	compose_shader_files_into_single_file(vs_file_name, fs_file_name, output_file_name)
