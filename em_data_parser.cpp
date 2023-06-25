#include <iostream>
#include <string>
#include <vector>

struct emData
{
    std::string filename;
    int start;
    int end;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please, provide a file.data as input." << std::endl;
        return 1;
    }
    FILE *handle = fopen(argv[1], "rb");

    std::vector<emData> fileInfo =
        {
            {"asset_dir/file01.png", 0, 12345},
            {"asset_dir/file02.png", 12345, 67890}};

    for (auto fInfo : fileInfo)
    {
        char *buffer = new char[(fInfo.end - fInfo.start) * sizeof(char)];
        size_t result = fread(buffer, fInfo.end - fInfo.start, 1, handle);

        FILE *output = fopen(fInfo.filename.c_str(), "wb");
        fwrite(buffer, fInfo.end - fInfo.start, 1, output);
        fclose(output);

        delete[] buffer;
    }

    fclose(handle);
}