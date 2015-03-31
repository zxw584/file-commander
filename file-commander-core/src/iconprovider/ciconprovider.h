#ifndef CICONPROVIDER_H
#define CICONPROVIDER_H

#include <unordered_map>
#include <memory>
#include "QtCoreIncludes"

class CFileSystemObject;
class CIconProvider
{
public:
	static const QIcon& iconForFilesystemObject(const CFileSystemObject& object);

private:
	CIconProvider();
	const QIcon& iconFor(const CFileSystemObject& object);

private:
	static std::shared_ptr<CIconProvider> _impl;

	std::unordered_map<quint64, QIcon> _iconCache;
	std::unordered_map<qulonglong, quint64>  _iconForObject;
};

#endif // CICONPROVIDER_H