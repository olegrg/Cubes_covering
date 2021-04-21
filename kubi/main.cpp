#include <bits/stdc++.h>

typedef std::vector<std::vector<std::vector<int> > > Field;


struct Delta
{
    int x;
    int y;
    int z;
};


class Cell
{
private:
    int x_coordinate;
    int y_coordinate;
    int z_coordinate;
public:
    Cell(int x = 0, int y = 0, int z = 0): x_coordinate(x), y_coordinate(y), z_coordinate(z) {}

    int get_x() const {return x_coordinate; }
    int get_y() const {return y_coordinate; }
    int get_z() const {return z_coordinate; }
    void set_x(int x) {x_coordinate = x; }
    void set_y(int y) {y_coordinate = y; }
    void set_z(int z) {z_coordinate = z; }
    void add_x(int x) {x_coordinate += x; }
    void add_y(int y) {y_coordinate += y; }
    void add_z(int z) {z_coordinate += z; }


};


void overlay_for_low_size_field(const Delta& delta, Field& field,
                                    int cube_size, int cubes_number) {
    Cell current_cube_corner;
    for (int i = 0; i < cubes_number; ++i) {
        for (int delta_x = 0; delta_x < cube_size; ++delta_x) {
            for (int delta_y = 0; delta_y < cube_size; ++delta_y) {
                for (int delta_z = 0; delta_z < cube_size; ++delta_z) {
                    field[(current_cube_corner.get_x() + delta_x)%field.size()]
                         [(current_cube_corner.get_y() + delta_y)%field.size()]
                         [(current_cube_corner.get_z() + delta_z)%field.size()] = 1;
                }
            }
        }
        current_cube_corner.add_x(delta.x);
        current_cube_corner.add_y(delta.y);
        current_cube_corner.add_z(delta.z);
    }
}


//in progress
/*overlaying_for_big_size_field(const Delta& delta, int cubes_number) {
    std::vector<Cell> cubes_corners(cubes_number);
    for (int i = 1; i < cubes_number; ++i) {
        cubes_corners[i].set_x(cubes_corners[i - 1].get_x() + delta.x);
    }

}*/


bool is_field_covered(Field& field) {
    for (int x = 0; x < field.size(); ++x) {
        for (int y = 0; y < field.size(); ++y) {
            for (int z = 0; z < field.size(); ++z) {
                if(field[x][y][z] == 0){
                    return false;
                }
            }
        }
    }
    return true;
}

void clear_field(Field& field) {
    for (int x = 0; x < field.size(); ++x) {
        for (int y = 0; y < field.size(); ++y) {
            for (int z = 0; z < field.size(); ++z) {
                field[x][y][z] = 0;
            }
        }
    }
}


int main()
{
    int field_size, cube_size, cubes_number;
    std::cout << "Enter the field size:" << '\n';
    std::cin >> field_size;
    std::cout << "Enter the cube size:" << '\n';
    std::cin >> cube_size;
    std::cout << "Enter the number of cubes:" << '\n';
    std::cin >> cubes_number;
    Delta delta;
    Field field(field_size, std::vector<std::vector<int> >(field_size, std::vector<int>(field_size)));
    for (int delta_x = 0; delta_x < field_size; ++ delta_x) {
        for (int delta_y = 0; delta_y < field_size; ++delta_y) {
            for (int delta_z = 0; delta_z < field_size; ++delta_z) {
                delta.x = delta_x;
                delta.y = delta_y;
                delta.z = delta_z;
                overlay_for_low_size_field(delta, field, cube_size, cubes_number);
                if (is_field_covered(field) ) {
                    std::cout << '{' << delta.x << ", " << delta.y << ", " << delta.z << '}' << '\n';
                }
                // std::cout << '{' << delta.x << ", " << delta.y << ", " << delta.z << '}' << '\n';
                clear_field(field);
            }
        }
    }
    return 0;
}
