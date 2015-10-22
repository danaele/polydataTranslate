#include "ExtractLabelSurfaces.h"

int ExtractPointData(std::string vtkLabelFile, std::string labelNameInfo, std::string arrayName)
{
    std::cout<<" Start ExtractPointData..."<<std::endl;
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
    std::cout<<"  Array name : "<<arrayName<<"\n  Number of components : "<<arrayType<<std::endl;
    //OutputFile
    std::ofstream outputFile;
    outputFile.open(labelNameInfo.c_str(),std::ofstream::out);
    if (outputFile.good())
    {
        outputFile << "#Text file containing label name information for each point - output of ExtractPointData tool \n";

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
    std::cout<<" ExtractPointData Done !\n"<<std::endl;
    return EXIT_SUCCESS;
}

int TranslateToLabelNumber(std::string labelNameInfo, std::string labelNumberInfo)
{
    std::cout<<" Start TranslateToLabelNumber..."<<std::endl;

    std::ifstream inputFile;
    inputFile.open(labelNameInfo.c_str(), std::ios::in);
    std::ofstream outputFile;
    outputFile.open(labelNumberInfo.c_str() , std::ios::out);
    std::ofstream logFile;
    logFile.open("logLabelTable" , std::ios::out);

    std::string labelLine;
    //Define map containing labels and a list of points associated to them
    std::map<std::string, int> labelMap;
    //Map iterator
    std::map< std::string , int >::const_iterator mit,mend;
    int labelNumber=0;
    //Extract labels and points associated
    if(inputFile) //file can be open
    {
        if(outputFile.good())
        {
            outputFile << "#Text file containing label number information for each point - output of TranslateToLabelNumber tool \n";
            getline(inputFile,labelLine); //format line
            getline(inputFile,labelLine);    //first labelName
            do
            {
                std::string newlabel=labelLine;
                if(labelMap.find(labelLine)!=labelMap.end())
                {
                    outputFile << labelMap[newlabel]<<"\n";
                }
                else
                {
                    labelNumber++;
                    labelMap[newlabel]=labelNumber;
                    outputFile << labelMap[newlabel]<<"\n";
                }
                getline(inputFile,labelLine);
            }while(!inputFile.eof());

        }
        else
        {
            std::cout<<"Cannot open  outputfile "<< labelNumberInfo<< std::endl;
            return EXIT_FAILURE;
        }
        outputFile.close();

        if(logFile.good())
        {
            logFile << "Matching table between labels names and labels numbers \n";
            for(mit=labelMap.begin(),mend=labelMap.end();mit!=mend;++mit)
            {
                logFile << mit->first << " : "<< mit->second << "\n";
            }
        }
        logFile.close();
        std::cout<<"  Number of labels : "<<labelNumber<<std::endl;
    }
    else
    {
        std::cout<<"Cannot open the inputfile "<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout<<" TranslateToLabelNumber Done !\n"<<std::endl;
    return EXIT_SUCCESS;
}

int CreateSurfaceLabelFiles(std::string vtkFile, std::string labelNumberInfo)
{
    //Check nb point vtkFile = nb point labelNumber


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
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run ExtractPointData and TranslateToLabelNumber tools ..."<<std::endl;
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !labelNumberInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo AND --labelNumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run ExtractPointData, TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !labelNumberInfo.empty() && !vtkFile.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo AND --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run TranslateToLabelNumber tool ..."<<std::endl;
        if(!labelNameInfo.empty() && !labelNumberInfo.empty())
        {
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNameInfo AND --labelNumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!labelNameInfo.empty() && !labelNumberInfo.empty() && !vtkFile.empty())
        {
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNameInfo AND --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==0 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run CreateSurfaceLabelFiles tool ..."<<std::endl;
        if(!labelNumberInfo.empty() && !vtkFile.empty())
        {
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else // case extractPointData==1 && translateToLabelNumber==0 && createSurfaceLabelFiles==1
    {
        std::cout<<"Wrong call";
        return EXIT_FAILURE;
    }
    std::cout<<"Done !"<<std::endl;
    return EXIT_SUCCESS ;
}
