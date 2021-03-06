/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2016 Mattijs Janssens
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::displacementFrozenLaplacianFvMotionSolver

Description
    Mesh motion solver for an fvMesh.  Based on solving the cell-centre
    Laplacian for the motion displacement.

SourceFiles
    displacementFrozenLaplacianFvMotionSolver.C

\*---------------------------------------------------------------------------*/

#ifndef displacementFrozenLaplacianFvMotionSolver_H
#define displacementFrozenLaplacianFvMotionSolver_H

#include "displacementMotionSolver.H"
#include "fvMotionSolverCore.H"
#include "fvMatricesFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward class declarations
class motionDiffusivity;

/*---------------------------------------------------------------------------*\
             Class displacementFrozenLaplacianFvMotionSolver Declaration
\*---------------------------------------------------------------------------*/

class displacementFrozenLaplacianFvMotionSolver
:
    public displacementMotionSolver,
    public fvMotionSolverCore
{
    // Private data

        //- Cell-centre motion field
        mutable volVectorField cellDisplacement_;

        //- Optionally read point-position field. Used only for position
        //  boundary conditions.
        mutable autoPtr<pointVectorField> pointLocation_;

        //- Diffusivity used to control the motion
        autoPtr<motionDiffusivity> diffusivityPtr_;

        //- Frozen points (that are not on patches). -1 or points that are
        //  fixed to be at points0_ location
        label frozenPointsZone_;

        //- Stored matrix

            autoPtr<fvVectorMatrix> laplacianEqn_;

//             //- Source term
//             Field<vector> source_;
// 
//             //- Boundary scalar field containing pseudo-matrix coeffs
//             //  for internal cells
//             FieldField<Field, vector> internalCoeffs_;
// 
//             //- Boundary scalar field containing pseudo-matrix coeffs
//             //  for boundary cells
//             FieldField<Field, vector> boundaryCoeffs_;
// 
//             surfaceVectorField *faceFluxCorrectionPtr_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        displacementFrozenLaplacianFvMotionSolver
        (
            const displacementFrozenLaplacianFvMotionSolver&
        );

        //- Disallow default bitwise assignment
        void operator=(const displacementFrozenLaplacianFvMotionSolver&);


public:

    //- Runtime type information
    TypeName("displacementFrozenLaplacian");


    // Constructors

        //- Construct from polyMesh and IOdictionary
        displacementFrozenLaplacianFvMotionSolver
        (
            const polyMesh&,
            const IOdictionary&
        );


    //- Destructor
    ~displacementFrozenLaplacianFvMotionSolver();


    // Member Functions

        //- Return reference to the cell motion displacement field
        volVectorField& cellDisplacement()
        {
            return cellDisplacement_;
        }

        //- Return const reference to the cell motion displacement field
        const volVectorField& cellDisplacement() const
        {
            return cellDisplacement_;
        }

        //- Return reference to the diffusivity field
        motionDiffusivity& diffusivity();

        //- Return point location obtained from the current motion field
        virtual tmp<pointField> curPoints() const;

        //- Solve for motion
        virtual void solve();

        //- Update topology
        virtual void updateMesh(const mapPolyMesh&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
