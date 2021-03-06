#pragma once

#include "Connection.h"
#include "OniFileDataSet.h"
#include <map>

/**
*
* This class keeps the Connection to the Database 
* and abstracts the DB from the main application.
*
* @author Florian Gref
* @author Pascal Mueller pascal_mueller@gmx.net
* 
*/

#define LOCAL_SAVEDIR "C:/Users/latadmin/Documents/gesturedetection4d/oniFiles"

class Datasource
{
private:
  Connection* conn;
public:
  Datasource(void);
  // Returns all the oniFiles which contains the gesture.
  std::vector <OniFileDataSet*> getOniFileDatasetsByGesture(char* gesture, int startIdx = -1, int endIdx = -1);
  // Returns all the oniFiles in the DB
  std::vector <OniFileDataSet*> getOniFileDatasets();
  // Looks up a special oniFIle by Name in the DB
  OniFileDataSet* getOniFileDataSetByName(char* name);

  // Creates a new OniFileDataSet and stores it in the DB.
  void createNewFileEntry(char* name,XnPoint3D* start, char* gesture, std::vector<XnPoint3D>& handPoints);
  std::map<int, char*> getGestureNames();

  ~Datasource(void);
};

