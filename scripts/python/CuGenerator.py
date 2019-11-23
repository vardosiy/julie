import os

#------------------------------------------------------------------------------

def generate_cu(target_dir, sources):
	destination_dir = os.path.join(target_dir, "cu")
	if not os.path.exists(destination_dir):
		os.mkdir(destination_dir)

	cu_filename = os.path.join(destination_dir, "cu.cpp")
	line_format = "#include \"{}\""

	cu = os.open(cu_filename, "w")
	for source_file in sources:
		cu.write(line_format.format(source_file))

#------------------------------------------------------------------------------
