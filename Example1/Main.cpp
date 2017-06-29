
#ifdef _WIN32 || WIN32 
#include <Windows.h>
#endif
#include "SVFDatabasePager.h"
#include "SVFComputeTools.h"
#include "osg/ShapeDrawable"

//readme:
//(1) Toggle Full Screen: F key
//(2) Reset camera: Control key
//(3) Rotate: Mouse left button + drag
//(4) Zoom: Mouse right button + drag or Mouse scroll
//(5) Exit: Esc key
//(6) Calculate SVF at a position: mouse click
int main(int argc, char **argv)
{

	 SVFComputeTools computeTools;
    // construct the viewer.
	 osgViewer::Viewer* viewer = new osgViewer::Viewer;
	 viewer->setUpViewAcrossAllScreens();
	 osg::ref_ptr<osg::Group> root = new osg::Group;
	 //load a 3D city model from file
	 //osg::ref_ptr<osg::Node> city = osgDB::readNodeFile(argv[1]); //create a model from argument
	 //osg::ref_ptr<osg::Node> city = osgDB::readNodeFile("./data/models/CAD/CAD.osg"); //use CAD model
	 osg::ref_ptr<osg::Node> city = osgDB::readNodeFile("./data/models/OAP3D/OAP3D.osgb"); //use OAP3D
	 root->addChild(city.get());

	 osg::ref_ptr<osgGA::CameraManipulator> manip = new osgGA::TrackballManipulator;
	 viewer->setCameraManipulator(manip.get());
	 root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	 viewer->setSceneData(root);
	 viewer->setThreadingModel(osgViewer::ViewerBase::ThreadingModel::ThreadPerContext);
	 viewer->addEventHandler(new osgViewer::ThreadingHandler);

	// add the window size toggle handler
	 viewer->addEventHandler(new osgViewer::WindowSizeHandler);

	// add the stats handler
	 viewer->addEventHandler(new osgViewer::StatsHandler);

	// add the LOD Scale handler
	 viewer->addEventHandler(new osgViewer::LODScaleHandler);

	viewer->addEventHandler(new SkyViewFactorEventHandler(city, root, manip, viewer));
	VGEDatabasePager* databasePager = new VGEDatabasePager;
	databasePager->resume();
	viewer->getScene()->setDatabasePager(databasePager);

    return viewer->run();
}



