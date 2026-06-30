#ifndef IPLATFORM_H
#define IPLATFORM_H

class IPlatform
{
public:
    virtual ~IPlatform() = default;

    virtual void setup() = 0;
};

#endif // IPLATFORM_H
