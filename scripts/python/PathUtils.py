import os

#------------------------------------------------------------------------------

def get_relative_paths(source_dir, items):
	return [os.path.relpath(item, source_dir) for item in items]

#------------------------------------------------------------------------------

def change_delimiters_to_unix_style(items):
	return [item.replace('\\', '/') for item in items]

#------------------------------------------------------------------------------
