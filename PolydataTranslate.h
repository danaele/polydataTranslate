#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkTransformPolyDataFilter.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <iterator>
#include <iostream>
#include <cstdio>
#include <vtkTransform.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>
#include <PolydataTranslateCLP.h>


vtkSmartPointer <vtkPolyData> ReadVTKFile ( std::string vtkFile ) ;
