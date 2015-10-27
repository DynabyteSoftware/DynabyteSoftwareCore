/***********************************************************************************************************************
 * @file ICloneable.h
 * @author Rod Leonard
 * @version 0.0.1
 * @date 2015/10/27
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * @brief Header file for DynabyteSoftware's ICloneable interface
 **********************************************************************************************************************/

#pragma once
namespace DynabyteSoftware
{
		/*********************************************************************************************************************
	 * @class ICloneable
	 * @ingroup DynabyteSoftware
	 * @brief ICloneable interface
	 * 
	 * @details
	 * This abstract class provides a templated clone() method that will return a copy of the object.
	 * @note Deep or shallow copy is not specified
	 ********************************************************************************************************************/
	template<class T>
	class ICloneable
	{
	protected:
		/**
		 * @return a clone of the object implementing this interface
		 **/
		virtual T& clone() const = 0;
	};
}