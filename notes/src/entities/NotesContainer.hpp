#ifndef __NOTES_CONTAINER_HPP__
#define __NOTES_CONTAINER_HPP__

//-----------------------------------------------------------------------------

class Note;
class NotesFolder;

//-----------------------------------------------------------------------------

class NotesContainer : boost::noncopyable
{
public:
	NotesContainer();
	~NotesContainer();

	void AddNote(std::unique_ptr<Note> _note, std::string_view _folder);

private:
	std::map<std::string, NotesFolder> m_folders;
};

//-----------------------------------------------------------------------------

#endif // __NOTES_CONTAINER_HPP__
