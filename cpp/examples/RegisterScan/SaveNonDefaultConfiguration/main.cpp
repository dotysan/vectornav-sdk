// The MIT License (MIT)
// 
// VectorNav SDK (v0.99.0)
// Copyright (c) 2024 VectorNav Technologies, LLC
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <filesystem>
#include <string>

#include "vectornav/HAL/File.hpp"
#include "vectornav/Interface/Registers.hpp"
#include "vectornav/Interface/Sensor.hpp"
#include "vectornav/RegisterScan.hpp"

using namespace VN;

std::string usage = "[port] [fileLocation or \"generic\"]";

enum class WriterType
{
    Xml,
    Ascii,
    Generic
};

int main(int argc, char* argv[])
{
    /*
    This save configuration example walks through the C++ usage of the SDK to save the current non-default configuration of a VectorNav unit into an XML file,
    ASCII file, or generic user-defined lambda expression.

    This example will achieve the following:
    1. Handle input arguments
    2. Instantiate a Sensor object and use it to connect to the VectorNav unit
    3. Save all non-default values from the VectorNav unit as specified
    4. Disconnect from the VectorNav unit
    */

    // 1. Handle input arguments
    if (argc > 3) { std::cerr << "Usage: SaveNonDefualtConfiguration " << usage << std::endl; };

    const std::string portName = (argc > 1) ? argv[1] : "COM1";  // Pass in port name as a positional argument, or edit here
    std::filesystem::path filePath = (argc > 2) ? argv[2] : (std::filesystem::path(__FILE__).parent_path() / "configSettings.xml");
    // std::filesystem::path filePath = "generic";

    WriterType writeType{WriterType::Generic};
    if (filePath.string() == std::string("generic")) { writeType = WriterType::Generic; }
    else
    {
        std::filesystem::path extension = filePath.extension();
        if (extension.empty()) { std::cerr << "Error: File path extension was not specified." << std::endl; }
        else if (extension == ".xml") { writeType = WriterType::Xml; }
        else { writeType = WriterType::Ascii; }
    }

    // 2. Instantiate a Sensor object and use it to connect to the VectorNav unit
    VN::Sensor sensor;
    Error latestError = sensor.autoConnect(portName);
    if (latestError != Error::None)
    {
        std::cerr << "Error " << latestError << " encountered when connecting to " + portName << std::endl;
        return static_cast<int>(latestError);
    }
    std::cout << "Connected to " << portName << " at " << sensor.connectedBaudRate().value() << std::endl;

    // 3. Save all non-default values from the VectorNav unit as specified  - There are a few different file types
    // that can be used to save the current non-default configuration settings from a VectorNav unit into
    // a configuration file, such as an XML file or text file. As part of the
    // RegisterScan::saveNonDefaultConfiguration() method, a Restore Factory Settings command will be issued
    // to the VectorNav unit. When using this method, it is highly recommended to monitor the progress of
    // this call as any errors encountered could mean that the settings previously configured were not able
    // to be reapplied onto the unit. If performing a Restore Factory Settings command is not desired, the
    // RegisterScan::saveConfiguration() method should instead be used to save the current configuration of
    // a VectorNav unit.
    VN::Error saveConfigError;
    switch (writeType)
    {
        case (WriterType::Xml):
        {
            RegisterScan::XmlConfigWriter writer(sensor, filePath.string());
            saveConfigError = RegisterScan::saveNonDefaultConfiguration(sensor, writer);
        }
        break;
        case (WriterType::Ascii):
        {
            RegisterScan::AsciiConfigWriter writer(filePath.string());
            saveConfigError = RegisterScan::saveNonDefaultConfiguration(sensor, writer);
        }
        break;
        case (WriterType::Generic):
        {
            RegisterScan::GenericConfigWriter cout_writer(
                [](const AsciiMessage& msg)
                {
                    std::cout << msg.c_str();
                    return Error::None;
                });
            saveConfigError = RegisterScan::saveNonDefaultConfiguration(sensor, cout_writer);
        }
        break;
        default:
            VN_ABORT();
    }
    if (saveConfigError != Error::None)
    {
        std::cerr << "Error " << saveConfigError << " occured when saving configuration." << std::endl;
        return 1;
    }

    // 4. Disconnect from the VectorNav unit
    sensor.disconnect();
    std::cout << "SaveNonDefaultConfiguration example complete." << std::endl;
}
