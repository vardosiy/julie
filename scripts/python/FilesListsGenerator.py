import os

from FilesCollector import FilesCollector
from PathUtils import *

#------------------------------------------------------------------------------

class FilesListsGenerator:

	def __init__(self, dirs):
		self._dirs = dirs

#------------------------------------------------------------------------------

	def generate_files_lists(self, cmake_variable, output_file_name, extensions):
		for dir in self._dirs:
			files = self._collect_files(dir, extensions)
			files = change_delimiters_to_unix_style(files)

			self._write_to_file(cmake_variable, output_file_name, dir, files)

#------------------------------------------------------------------------------

	def _collect_files(self, dir, extensions):
		collector = FilesCollector(extensions)

		files = collector.collect_files(dir)
		files = get_relative_paths(dir, files)

		return files

#------------------------------------------------------------------------------

	def _write_to_file(self, cmake_variable, output_file_name, dir, files):
		if len(files) == 0:
			return

		output_file_path = os.path.join(dir, output_file_name)
		output_file = open(output_file_path, "w")

		output_file.write("set(\n")
		output_file.write("\t" + cmake_variable + "\n")
		for file in files:
			output_file.write("\t" + file + "\n")
		output_file.write(")")

		output_file.close()

#------------------------------------------------------------------------------
