import os

#------------------------------------------------------------------------------

class FilesCollector:

	def __init__(self, extensions):
		self._extensions = extensions

#------------------------------------------------------------------------------

	def collect_files(self, dir):
		result = []

		dir_content = os.listdir(dir)
		for item_name in dir_content:
			item_path = os.path.join(dir, item_name)

			if os.path.isdir(item_path):
				result.extend(self.collect_files(item_path))
			elif self._is_required_file(item_path):
				result.append(item_path)

		return result

#------------------------------------------------------------------------------

	def _is_required_file(self, file):
		return os.path.splitext(file)[1] in self._extensions

#------------------------------------------------------------------------------
