#include "cimageviewerplugin.h"
#include "cimageviewerwindow.h"
#include "QtIncludes.h"

CImageViewerPlugin::CImageViewerPlugin()
{
}

bool CImageViewerPlugin::canViewCurrentFile() const
{
	const QString currentItem(_proxy->currentItemPath());
	if (currentItem.isEmpty())
		return false;
	
	QImageReader imageReader(currentItem);
	if (!imageReader.canRead())
		return false;
	else
		return !imageReader.read().isNull(); // TODO: find a more lightweight way to deal with non-image files for which canRead() returns 'true'
}

CPluginWindow* CImageViewerPlugin::viewCurrentFile()
{
	CImageViewerWindow * widget = new CImageViewerWindow;
	widget->displayImage(_proxy->currentItemPath());
	return widget;
}

QString CImageViewerPlugin::name()
{
	return "Image viewer plugin";
}


CFileCommanderPlugin* createPlugin()
{
	return new CImageViewerPlugin;
}