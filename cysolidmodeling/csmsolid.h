// Solid...

#include "csmfwddecl.hxx"

DLL_CYSOLIDMODELING CONSTRUCTOR(struct csmsolid_t *, csmsolid_duplicate, (const struct csmsolid_t *solid));

DLL_CYSOLIDMODELING void csmsolid_free(struct csmsolid_t **solido);


// Transformations...

DLL_CYSOLIDMODELING void csmsolid_move(struct csmsolid_t *solid, double dx, double dy, double dz);

DLL_CYSOLIDMODELING void csmsolid_rotate(
                    struct csmsolid_t *solid,
                    double angulo_rotacion_rad,
                    double Xo, double Yo, double Zo, double Ux, double Uy, double Uz);

DLL_CYSOLIDMODELING void csmsolid_general_transform(
                    struct csmsolid_t *solid,
                    double Ux, double Uy, double Uz, double Dx,
                    double Vx, double Vy, double Vz, double Dy,
                    double Wx, double Wy, double Wz, double Dz);


// Properties...

DLL_CYSOLIDMODELING double csmsolid_volume(const struct csmsolid_t *solid);
