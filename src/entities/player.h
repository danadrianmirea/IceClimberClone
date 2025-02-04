#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <optional>
#include <entity.h>
#include <entity_manager.h>
#include <state_machine.h>
#include <sprite.h>
#include <collision/collision.h>
#include <AABB/AABB.h>
#include <algorithm>
#include <defines.h>

using namespace std;

class Player: public IEntity
{
  bool headedToRight = true;
  int lowestCellYReached = 9999;
  uint8_t prevPressedKeys = KeyboardKeyCode::IC_KEY_NONE;
  uint8_t pressedKeys = KeyboardKeyCode::IC_KEY_NONE;
  void ProcessPressedKeys(bool = true);
  void ProcessReleasedKeys();
  void LoadNextSprite();
  bool PlayerIsQuiet();
  void UpdatePreviousDirection();
  void GetSolidCollisions(std::vector<ObjectCollision>&, bool&);
  void DisplacePlayerIfUnderlyingSurfaceIsMobile();
  void CorrectPlayerPositionOnReachScreenEdge();

  // Jump trajectory data
  float hInitialJumpSpeed = 0.0f;
  float vInitialJumpSpeed = 0.0f;
  float tJump = 0.0f;
  float hInitialJumpPosition = 0.0f;
  float vInitialJumpPosition = 0.0f;
  float previous_vOffset = 0.0f;

  // Fall trajectory data
  float hInitialFallSpeed = 0.0f;
  float vInitialFallSpeed = 0.0f;
  float tFall = 0.0f;
  float hInitialFallPosition = 0.0f;
  float vInitialFallPosition = 0.0f;

  // Slip data
  float hInitialSlipPosition = 0.0f;

  // Player global physics values
  uint16_t hMomentum = 0;
  const uint16_t maxMomentum = 15;
  collision::vec2<int16_t> prevVectorDirection;
  std::optional<SurfaceType> underlyingObjectSurfaceType;
  IEntity* prevUnderlyingCloud = nullptr;
  IEntity* currentUnderlyingCloud = nullptr;
  std::vector<IEntity*> objectsToIgnoreDuringFall;

  // Player action states
  bool isRunning = false;          // Player is running on a floor
  bool isJumping = false;          // Player is jumping (parabolic trajectory)
  bool isHitting = false;          // Player is hitting with the hammer
  bool isFalling = false;          // Player is falling
  bool isSlipping = false;         // Player is slipping on a sliding floor
  bool isJumpApex = false;         // Player is at the the max altitude during a jump
  bool isBlockedRight = false;     // Player is stuck running to the right towards a brick
  bool isBlockedLeft = false;      // Player is stuck running to the left towards a brick
  bool isOnMobileSurface = false;  // Player underlying surface is mobile

  // Player action update functions
  void UpdateCollisions();
  void MoveTo(Direction);
  void Jump(float vSpeed, float hSpeed);
  void UpdateJump();
  void FinishJump();
  void FallDueToLateralCollisionJump();
  void FallDueToSuspendedInTheAir();
  void Fall(float hSpeed);
  void UpdateFall();
  void FinishFall();
  void Slip();
  void UpdateSlip();
  void FinishSlip();
public:
  Player();
  ~Player() override;
  void InitWithSpriteSheet(EntitySpriteSheet*) override;
  void PrintName() override;
  bool Update(uint8_t) override;
  void NotifyNewAltitudeHasBeenReached();
  static IEntity* Create();

  // state machine triggers
  void RightKeyPressed();
  void RightKeyReleased();
  void LeftKeyPressed();
  void LeftKeyReleased();
  void UpKeyPressed();
  void SpaceKeyPressed();
  void DownKeyPressed();
  void JumpLanding();
  void FallLanding();
  void TopCollisionDuringJump();
  void LateralCollisionDuringJump();
  void RightKeyPressedAtJumpApex();
  void LeftKeyPressedAtJumpApex();
  void SuspendedInTheAir();
  void StopRunningOnSlidingSurface();
  void StopSlipping();
  bool ShouldBeginAnimationLoopAgain();

private:
  // state machine state functions
  void STATE_Idle_Right();
  void STATE_Idle_Left();
  void STATE_Run_Right();
  void STATE_Run_Left();
  void STATE_Jump_Idle_Right();
  void STATE_Jump_Idle_Left();
  void STATE_Jump_Run_Right();
  void STATE_Jump_Run_Left();
  void STATE_Fall_Idle_Right();
  void STATE_Fall_Idle_Left();
  void STATE_Fall_Run_Right();
  void STATE_Fall_Run_Left();
  void STATE_Fall_Jump_Run_Right();
  void STATE_Fall_Jump_Run_Left();
  void STATE_Hit_Right();
  void STATE_Hit_Left();
  void STATE_Slip_Right();
  void STATE_Slip_Left();

  // state map to define state function order
  BEGIN_STATE_MAP
      STATE_MAP_ENTRY(&Player::STATE_Idle_Right)
      STATE_MAP_ENTRY(&Player::STATE_Idle_Left)
      STATE_MAP_ENTRY(&Player::STATE_Run_Right)
      STATE_MAP_ENTRY(&Player::STATE_Run_Left)
      STATE_MAP_ENTRY(&Player::STATE_Jump_Idle_Right)
      STATE_MAP_ENTRY(&Player::STATE_Jump_Idle_Left)
      STATE_MAP_ENTRY(&Player::STATE_Jump_Run_Right)
      STATE_MAP_ENTRY(&Player::STATE_Jump_Run_Left)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Idle_Right)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Idle_Left)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Run_Right)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Run_Left)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Jump_Run_Right)
      STATE_MAP_ENTRY(&Player::STATE_Fall_Jump_Run_Left)
      STATE_MAP_ENTRY(&Player::STATE_Hit_Right)
      STATE_MAP_ENTRY(&Player::STATE_Hit_Left)
      STATE_MAP_ENTRY(&Player::STATE_Slip_Right)
      STATE_MAP_ENTRY(&Player::STATE_Slip_Left)
  END_STATE_MAP

  // state enumeration order must match the order of state
  // method entries in the state map
  enum PlayerStateIdentificator {
      STATE_IDLE_RIGHT = 0, // Initial state
      STATE_IDLE_LEFT,
      STATE_RUN_RIGHT,
      STATE_RUN_LEFT,
      STATE_JUMP_IDLE_RIGHT,
      STATE_JUMP_IDLE_LEFT,
      STATE_JUMP_RUN_RIGHT,
      STATE_JUMP_RUN_LEFT,
      STATE_FALL_IDLE_RIGHT,
      STATE_FALL_IDLE_LEFT,
      STATE_FALL_RUN_RIGHT,
      STATE_FALL_RUN_LEFT,
      STATE_FALL_JUMP_RUN_RIGHT,
      STATE_FALL_JUMP_RUN_LEFT,
      STATE_HIT_RIGHT,
      STATE_HIT_LEFT,
      STATE_SLIP_RIGHT,
      STATE_SLIP_LEFT,
      POPO_MAX_STATES
  };
};

#endif
