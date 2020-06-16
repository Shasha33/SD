#ifndef HW01_CLI_IOUTPUTCHANNEL_H
#define HW01_CLI_IOUTPUTCHANNEL_H


// Abstraction for entity, which will store the data.
// Command can write data into the channel, which will
// accumulate data in itself
template<class T>
class IOutputChannel {
public:
    // Writes data into the channel
    virtual void write(const T &x) = 0;

    virtual ~IOutputChannel() = default;
};


#endif //HW01_CLI_IOUTPUTCHANNEL_H
