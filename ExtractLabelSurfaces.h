#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkThreshold.h>
#include <vtkThresholdPoints.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vtkPointData.h>
#include <ExtractLabelSurfacesCLP.h>
#include <list>
#include <map>
#include <vtkUnstructuredGrid.h>

#include <vtkVersion.h>
#include <vtkIntArray.h>
#include <vtkCellData.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkThreshold.h>



int ExtractPointData(std::string vtkLabelFile, std::string labelNameInfo, std::string arrayName) ;
int TranslateToLabelNumber(std::string labelNameInfo, std::string labelNumberInfo) ;
int CreateSurfaceLabelFiles(std::string vtkFile, std::string labelNumberInfo) ;
vtkSmartPointer<vtkPolyData> ReadVTKFile(std::string vtkFile) ;
