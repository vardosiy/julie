import os
import sys

from FilesCollector import FilesCollector

#------------------------------------------------------------------------------

def generate_sources(parent_dir, project_names):
	for project in project_names:
		files = collect_files(project, [".cpp", ".hpp"], True)

		output_file_path = os.path.join(parent_dir, project, "InitSources.cmake")
		output_file = open(output_file_path, "w")

		output_file.write("set (SOURCES\n")
		for file in files:
			output_file.write("\t" + file + "\n")
		output_file.write(")")

#------------------------------------------------------------------------------

def collect_files(source_dir, extension, change_delimiters):
	collecter = FilesCollector(source_dir, extension)
	result = collecter.run()

	if change_delimiters:
		result = change_delimiters_to_unix_style(result)

	return result

#------------------------------------------------------------------------------

def change_delimiters_to_unix_style(files_list):
	result = []

	for file_name in files_list:
		result.append(file_name.replace('\\', '/'))

	return result

#------------------------------------------------------------------------------
