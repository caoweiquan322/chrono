// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban, Asher Elmquist, Evan Hoerl, Shuo He
// =============================================================================
//
// CityBus rigid tire subsystem
//
// =============================================================================

#include <algorithm>

#include "chrono_vehicle/ChVehicleModelData.h"
#include "chrono_models/vehicle/citybus/CityBus_RigidTire.h"

namespace chrono {
namespace vehicle {
namespace citybus {

// -----------------------------------------------------------------------------
// Static variables
// -----------------------------------------------------------------------------

const double CityBus_RigidTire::m_radius = .525;  //.545; //(26.49/2.0)*0.0254;
const double CityBus_RigidTire::m_width = .305;   // 8.07 * 0.0254;

const double CityBus_RigidTire::m_mass = 68.6;
const ChVector<> CityBus_RigidTire::m_inertia(6.104, 12.0, 6.104);

const std::string CityBus_RigidTire::m_meshFile = "citybus/CityBusTire.obj";

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
CityBus_RigidTire::CityBus_RigidTire(const std::string& name, bool use_mesh) : ChRigidTire(name) {
    SetContactFrictionCoefficient(0.9f);
    SetContactRestitutionCoefficient(0.1f);
    SetContactMaterialProperties(2e17f, 0.3f);
    SetContactMaterialCoefficients(2e5f, 40.0f, 2e5f, 20.0f);

    if (use_mesh) {
        SetMeshFilename(GetDataFile("citybus/CityBusTire.obj"), 0.005);
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void CityBus_RigidTire::AddVisualizationAssets(VisualizationType vis) {
    if (vis == VisualizationType::MESH) {
        m_trimesh_shape = AddVisualizationMesh(vehicle::GetDataFile(m_meshFile),   // left side
                                               vehicle::GetDataFile(m_meshFile));  // right side
    } else {
        ChRigidTire::AddVisualizationAssets(vis);
    }
}

void CityBus_RigidTire::RemoveVisualizationAssets() {
    ChRigidTire::RemoveVisualizationAssets();
    RemoveVisualizationMesh(m_trimesh_shape);
}

}  // end namespace citybus
}  // end namespace vehicle
}  // end namespace chrono
