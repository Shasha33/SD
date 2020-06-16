#ifndef HW01_CLI_IINPUTCHANNEL_H
#define HW01_CLI_IINPUTCHANNEL_H


// Abstraction for entity, which will provide data for command
// as an input stream, so command will read data from input channel
template<class T>
class IInputChannel {
public:

    // Checks whether or not channel has a data to provide into command
    virtual bool empty() const = 0;

    // Reads data from the channel. Data should be remove from the channel
    // after being read
    virtual T read() = 0;

    virtual ~IInputChannel() = default;
};


#endif //HW01_CLI_IINPUTCHANNEL_H
