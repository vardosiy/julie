import os

#------------------------------------------------------------------------------

class FilesCollector:

	def __init__(self, extensions, dir):
		self.__init_conteiners(extensions)
		self.__collect_files(dir)

#------------------------------------------------------------------------------

	def get_files_by_extension(self, extension):
		return self.__files.get(extension)

#------------------------------------------------------------------------------

	def __init_conteiners(self, extensions):
		self.__files = dict()
		for extension in extensions:
			self.__files[extension] = list()

#------------------------------------------------------------------------------

	def __collect_files(self, dir):
		dir_content = os.listdir(dir)
		for item_name in dir_content:
			item_path = os.path.join(dir, item_name)
			if os.path.isdir(item_path):
				self.__collect_files(item_path)
			else:
				self.__process_file(item_path)

#------------------------------------------------------------------------------

	def __process_file(self, file):
		file_extenstion = os.path.splitext(file)[1]

		if file_extenstion in self.__files.keys():
			self.__files[file_extenstion].append(file)

#------------------------------------------------------------------------------
