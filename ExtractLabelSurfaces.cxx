#include "ExtractLabelSurfaces.h"

int ExtractPointData(std::string vtkLabelFile, std::string labelNameInfo, std::string arrayName)
{
    // ReadFile vtkLabelFile
    vtkSmartPointer< vtkPolyDataReader > reader = vtkSmartPointer< vtkPolyDataReader >::New() ;
    vtkSmartPointer< vtkPolyData > polyData = vtkSmartPointer< vtkPolyData >::New() ;
    reader->SetFileName( vtkLabelFile.c_str() ) ;
    reader->OpenVTKFile();
    reader->Update() ;
    polyData = reader->GetOutput() ;
    //Checked if surface file with color no containing errors
    if (reader->GetErrorCode() !=0 )
    {
        std::cerr << "Unable to open input file: " << vtkLabelFile.c_str() << std::endl ;
        return EXIT_FAILURE ;
    }

    //Search array name specified exist in this vtk file
    vtkPointData* pointdata =  polyData->GetPointData();
    int arrayId=0;
    bool arrayFound=false;
    //Search all array in File
    for(unsigned i = 0; i < pointdata->GetNumberOfArrays(); i++)
    {
        if(pointdata->GetArrayName(i)==arrayName)
        {
            arrayId=i;
            arrayFound=true;
        }
    }
    if(arrayFound!=true)
    {
        std::cout<<"Array containing label specified not found"<<std::endl;
        return EXIT_FAILURE;
    }


    int arrayType = pointdata->GetArray(arrayId)->GetNumberOfComponents();

    //OutputFile
    std::ofstream outputFile;
    std::string fileTittle = labelNameInfo;
    fileTittle += ".txt";
    outputFile.open(fileTittle.c_str(),std::ofstream::out);
    if (outputFile.good())
    {
        outputFile << "#!ascii file from ExtractPointData tool \n";

        //Write in the file all labels corresponding to each points - in the same order
        for(vtkIdType j = 0; j < polyData->GetNumberOfPoints(); j++)
        {
            double vec[arrayType];  //search type
            pointdata->GetArray(arrayId)->GetTuple(j,vec);
            for(int k = 0 ; k < arrayType; k++)
            {
               outputFile << vec[k] <<" ";
            }
            outputFile <<"\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to open file"<<std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int TranslateToLabelNumber(std::string labelNameInfo, std::string labelNumberInfo)
{
    //std::ifstream inputfile(labelNameInfo);
    return EXIT_SUCCESS;
}

int CreateSurfaceLabelFiles(std::string vtkFile, std::string labelNumberInfo)
{
    return EXIT_SUCCESS;
}

int main ( int argc, char *argv[] )
{
    PARSE_ARGS;

    if(extractPointData==0 && translateToLabelNumber==0 && createSurfaceLabelFiles==0 )
    {
        std::cout<<"Nothing to do. Specified at leat one action (--extractPointData or --translateToLabelNumber or --createSurfaceLabelFiles)"<<std::endl;
        return EXIT_FAILURE;
    }
    else if(extractPointData==1 && translateToLabelNumber==0 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run ExtractPointData tool ..."<<std::endl;
        if(!vtklabelFile.empty() && !labelnameInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtklabelFile, labelnameInfo, arrayName);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --vtklabelFile AND --arrayName AND --labelnameInfo "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run ExtractPointData and TranslateToLabelNumber tools ..."<<std::endl;
        if(!vtklabelFile.empty() && !labelnameInfo.empty() && !labelnumberInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtklabelFile, labelnameInfo, arrayName);
            TranslateToLabelNumber(labelnameInfo, labelnumberInfo);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --vtklabelFile AND --arrayName AND --labelnameInfo AND --labelnumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run ExtractPointData, TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!vtklabelFile.empty() && !labelnameInfo.empty() && !labelnumberInfo.empty() && !vtkFile.empty() && !arrayName.empty())
        {
            ExtractPointData(vtklabelFile, labelnameInfo, arrayName);
            TranslateToLabelNumber(labelnameInfo, labelnumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelnumberInfo);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --vtklabelFile AND --arrayName AND --labelnameInfo AND --labelnumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run TranslateToLabelNumber tool ..."<<std::endl;
        if(!labelnameInfo.empty() && !labelnumberInfo.empty())
        {
            TranslateToLabelNumber(labelnameInfo, labelnumberInfo);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --labelnameInfo AND --labelnumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!labelnameInfo.empty() && !labelnumberInfo.empty() && !vtkFile.empty())
        {
            TranslateToLabelNumber(labelnameInfo, labelnumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelnumberInfo);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --labelnameInfo AND --labelnumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==0 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run CreateSurfaceLabelFiles tool ..."<<std::endl;
        if(!labelnumberInfo.empty() && !vtkFile.empty())
        {
            CreateSurfaceLabelFiles(vtkFile, labelnumberInfo);
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout<<"You need to specify --labelnumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else // case extractPointData==1 && translateToLabelNumber==0 && createSurfaceLabelFiles==1
    {
        std::cout<<"Wrong call";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS ;
}
