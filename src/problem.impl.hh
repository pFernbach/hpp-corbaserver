// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_CORBASERVER_PROBLEM_IMPL_HH
# define HPP_CORBASERVER_PROBLEM_IMPL_HH
# include <vector>
# include <stdlib.h>

# include "hpp/corbaserver/fwd.hh"
# include "hpp/corbaserver/problem.hh"
# include "hpp/corbaserver/problem-solver-map.hh"

# include "hpp/corbaserver/deprecated.hh"

namespace hpp
{
  namespace corbaServer
  {
    namespace impl
    {
      using CORBA::Long;
      using CORBA::ULong;
      /// \brief Implement CORBA interface ``Problem''.
      class Problem : public virtual POA_hpp::corbaserver::Problem
      {
      public:
	Problem (corbaServer::Server* server);

        virtual Names_t* getAvailable (const char* what) throw (hpp::Error);

        virtual bool selectProblem (const char* problemName) throw (hpp::Error);

	virtual void
	setRandomSeed (const Long seed) throw (hpp::Error) {
          srand ((int) seed);
        }

	virtual void
	setInitialConfig (const hpp::floatSeq& dofArray) throw (hpp::Error);

	virtual hpp::floatSeq*
	getInitialConfig () throw (hpp::Error);

	virtual void
	addGoalConfig (const hpp::floatSeq& dofArray) throw (hpp::Error);

	virtual hpp::floatSeqSeq*	getGoalConfigs () throw (hpp::Error);

	virtual void
	resetGoalConfigs ()  throw (hpp::Error);

	virtual void createOrientationConstraint
	(const char* constraintName, const char* joint1Name,
	 const char* joint2Name, const Double* p, const hpp::boolSeq& mask)
	  throw (hpp::Error);

	virtual void createTransformationConstraint
	(const char* constraintName, const char* joint1Name,
	 const char* joint2Name, const Transform_ p, const hpp::boolSeq& mask)
	  throw (hpp::Error);

        void createRelativeComConstraint (const char* constraintName,
            const char* comn, const char* jointName, const floatSeq& point,
            const hpp::boolSeq& mask)
          throw (hpp::Error);

        void createComBeetweenFeet (const char* constraintName, const char* comn,
            const char* jointLName, const char* jointRName,
            const floatSeq& pointL, const floatSeq& pointR,
            const char* jointRefName, const hpp::boolSeq& mask)
          throw (hpp::Error);

	virtual void createStaticStabilityGravityConstraint
	(const char* constraintName, const Names_t& floorJoints,
	 const Names_t& objectJoints,
         const hpp::floatSeqSeq& points, const hpp::intSeqSeq& objTriangles,
         const hpp::intSeqSeq& floorTriangles)
	  throw (hpp::Error) HPP_CORBASERVER_DEPRECATED;

	virtual void createConvexShapeContactConstraint
        (const char* constraintName, const Names_t& floorJoints,
         const Names_t& objectJoints,
         const hpp::floatSeqSeq& points, const hpp::intSeqSeq& objTriangles,
         const hpp::intSeqSeq& floorTriangles)
	  throw (hpp::Error);

        void createStaticStabilityConstraint (
            const char* constraintName, const hpp::Names_t& jointNames,
            const hpp::floatSeqSeq& points, const hpp::floatSeqSeq& normals,
            const char* comRootJointName)
          throw (hpp::Error);

	virtual void createPositionConstraint (const char* constraintName,
					       const char* joint1Name,
					       const char* joint2Name,
					       const hpp::floatSeq& point1,
					       const hpp::floatSeq& point2,
					       const hpp::boolSeq& mask)
	  throw (hpp::Error);

	virtual void createConfigurationConstraint (const char* constraintName,
					       const hpp::floatSeq& goal)
	  throw (hpp::Error);

	virtual void createDistanceBetweenJointConstraint
	(const char* constraintName, const char* joint1Name,
	 const char* joint2Name, Double distance) throw (Error);

	virtual void createDistanceBetweenJointAndObjects
	(const char* constraintName, const char* joint1Name,
	 const hpp::Names_t& objects, Double distance) throw (Error);

	virtual bool applyConstraints (const hpp::floatSeq& input,
				       hpp::floatSeq_out output,
				       Double& residualError)
	  throw (hpp::Error);

	virtual void computeValueAndJacobian
	(const hpp::floatSeq& config, hpp::floatSeq_out value,
	 hpp::floatSeqSeq_out jacobian) throw (hpp::Error);

	virtual bool generateValidConfig (UShort maxIter,
				       hpp::floatSeq_out output,
				       Double& residualError)
	  throw (hpp::Error);

        virtual void addPassiveDofs (const char* constraintName,
                                    const hpp::Names_t& dofName)
          throw (hpp::Error);

        virtual void setConstantRightHandSide (const char* constraintName,
					       CORBA::Boolean constant)
          throw (hpp::Error);

        virtual bool getConstantRightHandSide (const char* constraintName)
          throw (hpp::Error);

	virtual void resetConstraints () throw (hpp::Error);
	virtual void setNumericalConstraints
	(const char* constraintName, const hpp::Names_t& constraintNames,
         const hpp::intSeq& priorities)
	  throw (Error);
	virtual void lockJoint (const char* jointName,
				const hpp::floatSeq& value)
	  throw (hpp::Error);
	virtual void resetGoalConstraints () throw (hpp::Error);
	virtual void setGoalNumericalConstraints
	(const char* constraintName, const hpp::Names_t& constraintNames,
         const hpp::intSeq& priorities)
	  throw (Error);
	virtual void addGoalLockJoint (const char* jointName,
				const hpp::floatSeq& value)
	  throw (hpp::Error);
	virtual void setErrorThreshold (Double threshold) throw (Error);
	virtual void setMaxIterations (UShort iterations) throw (Error);

	virtual void addPathOptimizer (const char* pathOptimizerType)
	  throw (Error);

	virtual void clearPathOptimizers () throw (Error);

	virtual void selectPathValidation (const char* pathValidationType,
					   Double tolerance) throw (Error);

        virtual void selectPathProjector (const char* pathProjectorType,
                                          Double tolerance) throw (Error);

	virtual void selectPathPlanner (const char* pathPlannerType)
	  throw (Error);

    virtual void selectSteeringMethod (const char* steeringMethodType)
      throw (Error);

    virtual void selectConFigurationShooter (const char* configurationShooterType)
      throw (Error);

	virtual bool prepareSolveStepByStep () throw (hpp::Error);
	virtual bool executeOneStep () throw (hpp::Error);
	virtual void finishSolveStepByStep () throw (hpp::Error);

	virtual hpp::intSeq* solve () throw (hpp::Error);

	virtual bool directPath (const hpp::floatSeq& startConfig,
				  const hpp::floatSeq& endConfig, UShort& pathId)
	  throw (hpp::Error);

	virtual bool addConfigToRoadmap (const hpp::floatSeq& config) throw (hpp::Error);

	virtual bool addEdgeToRoadmap (const hpp::floatSeq& config1, const hpp::floatSeq& config2, 
				       UShort pathId, bool bothEdges) throw (hpp::Error);

	virtual void appendDirectPath (UShort pathId,
				       const hpp::floatSeq& config)
	  throw (hpp::Error);

	virtual bool projectPath (UShort pathId)
	  throw (hpp::Error);

	virtual void interruptPathPlanning () throw (hpp::Error);

	virtual Short numberPaths () throw (hpp::Error);

	virtual hpp::intSeq* optimizePath (UShort pathId) throw (hpp::Error);

	virtual Double pathLength (UShort pathId) throw (hpp::Error);

	virtual hpp::floatSeq* configAtParam (UShort pathId,
					      Double atDistance)
	  throw (hpp::Error);

	virtual hpp::floatSeqSeq* getWaypoints (UShort inPathId)
	  throw (hpp::Error);
	virtual hpp::floatSeqSeq* nodes () throw (hpp::Error);
	virtual Long numberEdges () throw (hpp::Error);
	virtual void edge (ULong edgeId, hpp::floatSeq_out q1,
			   hpp::floatSeq_out q2) throw (hpp::Error);
    virtual Long connectedComponentOfEdge (ULong edgeId) throw (hpp::Error);
    virtual hpp::floatSeq* node (ULong nodeId) throw (hpp::Error);
    virtual Long connectedComponentOfNode (ULong nodeId) throw (hpp::Error);
    virtual Long numberNodes () throw (hpp::Error);
	virtual Long numberConnectedComponents () throw (hpp::Error);
	virtual hpp::floatSeqSeq*
	nodesConnectedComponent (ULong connectedComponentId) throw (hpp::Error);
	
	virtual hpp::floatSeq*
	getNearestConfig (const hpp::floatSeq& config, const Long connectedComponentId, 
			  hpp::core::value_type& distance) throw (hpp::Error);
	
	virtual void clearRoadmap () throw (hpp::Error);
	virtual void resetRoadmap ();
        virtual void saveRoadmap (const char* filename) throw (hpp::Error);
        virtual void readRoadmap (const char* filename) throw (hpp::Error);

      private:
        /// Return the selected problem solver
        core::ProblemSolverPtr_t problemSolver ();
	/// \brief Pointer to the Server owning this object
	corbaServer::Server* server_;
      };
    } // end of namespace impl.
  } // end of namespace corbaServer.
} // end of namespace hpp.

#endif //! HPP_CORBASERVER_OBSTACLE_IMPL_HH
