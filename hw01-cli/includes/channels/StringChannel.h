#ifndef HW01_CLI_STRINGCHANNEL_H
#define HW01_CLI_STRINGCHANNEL_H

#include <channels/IInputChannel.h>
#include <channels/IOutputChannel.h>
#include <string>


// Implementation of IOChannel interfaces.
// It manipulates with data of string type.
// Can be used both as input and output channel
// during command execution.
class StringChannel :
        public IInputChannel<std::string>,
        public IOutputChannel<std::string> {
public:
    bool empty() const override;

    std::string read() override;

    void write(const std::string &x) override;

    // Appends symbol into the inner data buffer
    void write(char c);

    // Makes the data buffer empty
    void clear();

    // write data from file into this channel
    void writeFile(const std::string &fileName);

    // read data from the channel until meeting line separator character
    // if there is line separator then it will be added to the end of
    // line
    std::string readLine();
private:
    std::string buffer;
};


#endif //HW01_CLI_STRINGCHANNEL_H
