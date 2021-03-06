#include "cvolumeenumerator.h"
#include "volumeinfohelper.hpp"

DISABLE_COMPILER_WARNINGS
#include <QDir>
RESTORE_COMPILER_WARNINGS

const std::deque<VolumeInfo> CVolumeEnumerator::enumerateVolumesImpl()
{
	std::deque<VolumeInfo> volumes;

	for (const QString& volumeName: QDir("/Volumes/").entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden | QDir::System))
	{
		VolumeInfo info;
		info.rootObjectInfo = "/Volumes/" + volumeName;
		info.volumeLabel = volumeName;
		info.isReady = true;

		const auto sys_info = volumeInfoForPath(info.rootObjectInfo.fullAbsolutePath());
		info.volumeSize = sys_info.f_bsize * sys_info.f_blocks;
		info.freeSize = sys_info.f_bsize * sys_info.f_bavail;

		volumes.push_back(info);
	}

	return volumes;
}
