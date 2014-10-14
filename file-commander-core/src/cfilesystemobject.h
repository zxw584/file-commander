#ifndef CFILESYSTEMOBJECT_H
#define CFILESYSTEMOBJECT_H

#include <stdint.h>
#include <vector>
#include <memory>
#include "QtCoreIncludes"

#include "fileoperationresultcode.h"

enum FileSystemObjectType { UnknownType, Directory, File };

struct CFileSystemObjectProperties {
	QString  completeBaseName;
	QString  extension;
	QString  fullName;
	QString  parentFolder;
	QString  fullPath;
	FileSystemObjectType type;
	uint64_t size;
	time_t   creationDate;
	time_t   modificationDate;
	qulonglong hash;
	struct Permissions
	{
		Permissions() : read(false), write(false), exec(false) {}
		bool read;
		bool write;
		bool exec;
	} permissions;

	CFileSystemObjectProperties() : type(UnknownType), size(0), creationDate(0), modificationDate(0) {}
};

class QIcon;
class CFileSystemObject
{
public:
	CFileSystemObject ();
	explicit CFileSystemObject (const QFileInfo & fileInfo);
	virtual ~CFileSystemObject ();

// Information about this object
	bool exists() const;
	const CFileSystemObjectProperties& properties() const;
	FileSystemObjectType type() const;
	bool isFile() const;
	bool isDir () const;
	bool isCdUp() const; // returns true if it's ".." item
	bool isExecutable() const;
	bool isHidden() const;
	// Returns true if this object is a child of parent, either direct or indirect
	bool isChildOf(const CFileSystemObject& parent) const;
	QString absoluteFilePath() const;
	QString parentDirPath() const;
	const QIcon& icon() const;
	uint64_t size() const;
	qulonglong hash() const;
	const QFileInfo& qFileInfo() const;

	// A hack to store the size of a directory after it's calculated
	void setDirSize(uint64_t size);

	// File name without suffix, or folder name
	QString name() const;
	// Filename + suffix for files, same as name() for folders
	QString fullName() const;
	QString extension() const;
	QString sizeString() const;
	QString modificationDateString() const;

// Operations
	// Renames a dir or a file. Unlike move, it requires that destination is on the same volume
	FileOperationResultCode rename(const QString& newName, bool relativeName = false);
	FileOperationResultCode copyAtomically(const QString& destFolder, const QString& newName = QString());
	FileOperationResultCode moveAtomically(const QString& destFolder, const QString& newName = QString());

// Non-blocking file copy API
	// Requests copying the next (or the first if copyOperationInProgress() returns false) chunk of the file.
	FileOperationResultCode copyChunk(int64_t chunkSize, const QString& destFolder, const QString& newName = QString());
	FileOperationResultCode moveChunk(int64_t chunkSize, const QString& destFolder, const QString &newName = QString());
	bool copyOperationInProgress() const;
	uint64_t bytesCopied() const;
	FileOperationResultCode cancelCopy();

	bool                    makeWritable();
	FileOperationResultCode remove ();

	QString lastErrorMessage () const;

private:
	QFileInfo                   _fileInfo;
	CFileSystemObjectProperties _properties;
	QString                     _lastError;
	FileSystemObjectType        _type;

// For copying / moving
	std::shared_ptr<QFile>           _thisFile;
	std::shared_ptr<QFile>           _destFile;
};

#endif // CFILESYSTEMOBJECT_H
