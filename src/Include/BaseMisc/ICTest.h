#pragma once

[
	object ,
	uuid("724F8B49-B765-4c60-8D40-98CD246EC1A5") ,
	pointer_default(unique)
]
__interface ICBaseTest : IDispatch
{
	HRESULT Test	() ;
} ;

[
	object ,
	uuid("27A34A4A-DAFB-4d97-A66F-38D9147198D7") ,
	pointer_default(unique)
]
__interface ICBaseTestB : IDispatch
{
	HRESULT Test2	() ;
} ;