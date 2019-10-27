#pragma once
#include <vector>
#include <complex>
#include "Picture.h"
#include "GameObject.h"

struct UnitInfo;

class Grid 
{
public:   
    static constexpr int vSlotCnt = 11;
    static constexpr int hSlotCnt = 18;
    static constexpr float slotSize = 48.0f;
    static constexpr float width = hSlotCnt*slotSize;
    static constexpr float height = vSlotCnt*slotSize;
    
    template <class T>
    struct GridData
    {
        T* begin() { return &data[0][0]; };
        T* end() { return &data[0][0] + width*height; };
        const T* begin() const { return &data[0][0]; };
        const T* end() const { return &data[0][0] + width*height; };
        T* operator[](size_t ind) { return &data[ind][0]; };
        const T* operator[](size_t ind) const  { return &data[ind][0];  };
        static constexpr int width = hSlotCnt;
        static constexpr int height = vSlotCnt;
        T data[width][height];
    };
    
    class GridObject
    {
        public:
            typedef std::vector<std::pair<int, int> > GridSize;
            virtual ~GridObject() = default;
            std::complex<float> GetWorldPos() const;
            GridSize GetGridPos() const;
            virtual float GetSize() const = 0;
            virtual bool IsDestructable() const = 0;
            void AddToGrid(int grid_x, int grid_y, Grid* grid);
        protected:          
            GridObject(int grid_x, int grid_y, Grid* grid, int size = 1);
            GridObject(int size = 1);
            const Grid* grid;
            int grid_size;
            float x;
            float y;
    };
   
    Grid(float xx, float yy);   
    ~Grid();

    std::pair<int, int> GridPos(std::complex<float> pos) const;
    std::complex<float> WorldPos(std::pair<int, int> pos) const; 
    const float x;
    const float y;
    const std::vector<GridObject*>& GetUnits() const;
    void Enable(bool en = true);
private:
    std::vector<GridObject*> unit;
    Picture background;
};

