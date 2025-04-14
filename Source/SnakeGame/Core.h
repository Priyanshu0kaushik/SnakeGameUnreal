// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ESnakeDirection : uint8{
    UP =0,
    RIGHT =1,
    DOWN =2,
    LEFT =3,
    NONE = 255
};

constexpr float WORLD_HEIGHT = 30.f;
constexpr float WORLD_WIDTH= 30.f;

constexpr float TileSize = 100.f;
