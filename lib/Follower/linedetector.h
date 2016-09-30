#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

class LineDetector {
  public:
    virtual int detectLine() = 0;
    virtual int getLineMax() = 0;
};

#endif
