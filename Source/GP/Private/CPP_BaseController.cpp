// Fill out your copyright notice in the Description page of Project Settings.


#include "GP/Public/CPP_BaseController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "K2Node_DoOnceMultiInput.h"

ACharacter* ACPP_BaseController::GetControlledPlayer()
{
	return ControlledChar ? ControlledChar : Cast<ACPP_BaseCharacter>(GetPawn());
}

void ACPP_BaseController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(IsFalling())
		DoOnce = true;
	else
	{
		if(DoOnce)
		{
			OnReachGround();
			DoOnce = false;
		}
	}
}


void ACPP_BaseController::MoveForwardBackward(float AxisValue, bool Force)
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		auto ForwardVector = TempControlledChar->GetActorForwardVector();
		TempControlledChar->AddMovementInput(ForwardVector, AxisValue, Force);
	}
}

void ACPP_BaseController::MoveLeftRight(float AxisValue, bool Force)
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		auto RightVector = TempControlledChar->GetActorRightVector();
		TempControlledChar->AddMovementInput(RightVector, AxisValue, Force);
	}
}

void ACPP_BaseController::LookUpDown(float AxisValue, float Sensitivity)
{
	auto TempControlledChar = GetPawn();
	if(TempControlledChar)
	{
		TempControlledChar->AddControllerPitchInput(AxisValue * Sensitivity);
	}
}

void ACPP_BaseController::LookLeftRight(float AxisValue, float Sensitivity)
{
	auto TempControlledChar = GetPawn();
	if(TempControlledChar)
	{
		TempControlledChar->AddControllerYawInput(AxisValue * Sensitivity);
	}
}

void ACPP_BaseController::Jump()
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		TempControlledChar->Jump();
	}
}

void ACPP_BaseController::StopJumping()
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		TempControlledChar->StopJumping();
	}
}

void ACPP_BaseController::Crouch()
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		CrouchDelayed = IsFalling();
		if(!CrouchDelayed)
		{
			TempControlledChar->Crouch();
		}
	}
}

void ACPP_BaseController::StopCrouching()
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		TempControlledChar->UnCrouch();
		CrouchDelayed = false;
	}
}

void ACPP_BaseController::Sneak(float WalkSpeed)
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		auto CharacterMovement = TempControlledChar->GetCharacterMovement();
		CharacterMovement->MaxWalkSpeed = WalkSpeed;
	}
}

void ACPP_BaseController::StopSneaking(float RunSpeed)
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		auto CharacterMovement = TempControlledChar->GetCharacterMovement();
		CharacterMovement->MaxWalkSpeed = RunSpeed;
	}
}

/*Checkers*/
bool ACPP_BaseController::IsFalling()
{
	auto TempControlledChar = GetControlledPlayer();
	if(TempControlledChar)
	{
		auto CharacterMovement = TempControlledChar->GetCharacterMovement();
		return CharacterMovement->IsFalling();
	}
	return false;
}
