 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GP/Public/CPP_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CPP_BaseController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GP_API ACPP_BaseController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool CrouchDelayed;
	
	ACharacter* GetControlledPlayer();

	virtual void Tick(float DeltaSeconds) override;
	
	//Controlling
	UFUNCTION(BlueprintCallable)
	void MoveForwardBackward(float AxisValue, bool Force);

	UFUNCTION(BlueprintCallable)
	void MoveLeftRight(float AxisValue, bool Force);

	UFUNCTION(BlueprintCallable)
	void LookUpDown(float AxisValue, float Sensitivity);

	UFUNCTION(BlueprintCallable)
	void LookLeftRight(float AxisValue, float Sensitivity);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void StopJumping();

	UFUNCTION(BlueprintCallable)
	void Crouch();

	UFUNCTION(BlueprintCallable)
	void StopCrouching();
	
	UFUNCTION(BlueprintCallable)
	void Sneak(float WalkSpeed);
	
	UFUNCTION(BlueprintCallable)
    void StopSneaking(float RunSpeed);

	/***********************************/

	/*Events*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnReachGround();

	/*Checkers*/
	bool IsFalling();
	
	
	
private:
	ACPP_BaseCharacter *ControlledChar;
	bool DoOnce;
};
