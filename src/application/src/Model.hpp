#pragma once

#include "core/nodes/NodesFwd.hpp"
#include "utils/Singleton.hpp"

#include <string_view>

//-----------------------------------------------------------------------------

class Model : public utils::Singleton<Model>
{
	friend class utils::Singleton<Model>;

public:
	void save() const;
	void load();

private:
	Model() noexcept;
	~Model() noexcept;

	void writeHeader(std::ofstream & _stream) const;
	void readHeader(std::ifstream & _stream);
	void saveData(std::ofstream & _stream) const;
	void restoreData(std::ifstream & _stream);

private:
	nodes::NotesFolderPtr m_notesRoot;

	static constexpr std::string_view k_saveFile = "data.dat";
};

//-----------------------------------------------------------------------------
