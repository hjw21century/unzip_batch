#include <iostream>

#include <dirent.h>
#include <string.h>

using namespace std;

int readFileList(char const *basePath);

int main() {
    cout << "input the directry which the zipped files are in:" << endl;
    string sDir;
    cin >> sDir ;
    readFileList(sDir.c_str());
    return 0;
}

void unZipFile(char* fileName,char *basePath)
{
    char cmd[1024] = {0};
    strcpy(cmd,"unzip -o ");
    strcat(cmd,fileName);
    strcat(cmd," -d ");
    strcat(cmd,basePath);
    strcat(cmd,"unzipped");
    system(cmd);
}


int readFileList(char const  *basePath)
{
    DIR *dir;
    struct dirent *ptr;
    char basePathD[1024] = {0};
    char base[1000] = {0};
    char fullPath[1024] = {0};

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    strcpy(basePathD, basePath);

    if (*(basePathD+strlen(basePathD)-1) != '/')
    {
        strcat(basePathD,"/");
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
        {
            strcpy(fullPath,basePathD);
            strcat(fullPath,ptr->d_name);
            if (strcmp(ptr->d_name+(strlen(ptr->d_name)-3),"zip")==0|| \
            strcmp(ptr->d_name+(strlen(ptr->d_name)-3),"ZIP")==0)
            {
                unZipFile(fullPath,basePathD);
            }

            printf("d_name:%s%s\n",basePathD,ptr->d_name);

        }

        else if(ptr->d_type == 10)    ///link file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            //只读取当前目录下文件
            //readFileList(base);
        }
    }
    closedir(dir);
    return 1;
}
