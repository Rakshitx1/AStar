#pragma once

class Coordinate {
private:
    int x;
    int y;
    int f{};
    int g{};
    int h{};
    Coordinate* parent{};

public:
    Coordinate(int x, int y);
    ~Coordinate();
    void setF(int f);
    void setG(int g);
    void setH(int h);
    [[nodiscard]] int getF() const;
    [[nodiscard]] int getG() const;
    [[nodiscard]] int getH() const;
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] Coordinate* getParent() const;
    void setParent(Coordinate* parent);
    int distanceTo(Coordinate* other) const;

};