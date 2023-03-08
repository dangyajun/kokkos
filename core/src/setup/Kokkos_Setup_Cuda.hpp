//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#ifndef KOKKOS_CUDA_SETUP_HPP_
#define KOKKOS_CUDA_SETUP_HPP_

#if !defined(KOKKOS_ENABLE_CUDA)
#error \
    "KOKKOS_ENABLE_CUDA was not defined, but Kokkos_Setup_Cuda.hpp was included anyway."
#endif

#if defined(KOKKOS_ENABLE_CUDA) && !defined(__CUDACC__)
#error \
    "KOKKOS_ENABLE_CUDA defined but the compiler is not defining the __CUDACC__ macro as expected"
// Some tooling environments will still function better if we do this here.
#define __CUDACC__
#endif /* defined(KOKKOS_ENABLE_CUDA) && !defined(__CUDACC__) */

// Compiling with a CUDA compiler.
//
//  Include <cuda.h> to pick up the CUDA_VERSION macro defined as:
//    CUDA_VERSION = ( MAJOR_VERSION * 1000 ) + ( MINOR_VERSION * 10 )
//
//  When generating device code the __CUDA_ARCH__ macro is defined as:
//    __CUDA_ARCH__ = ( MAJOR_CAPABILITY * 100 ) + ( MINOR_CAPABILITY * 10 )

#include <cuda_runtime.h>
#include <cuda.h>

#if defined(_WIN32)
#define KOKKOS_IMPL_WINDOWS_CUDA
#endif

#if !defined(CUDA_VERSION)
#error "#include <cuda.h> did not define CUDA_VERSION."
#endif

#if defined(__CUDA_ARCH__) && (__CUDA_ARCH__ < 300)
// Compiling with CUDA compiler for device code.
#error "Cuda device capability >= 3.0 is required."
#endif

#ifdef KOKKOS_ENABLE_CUDA_LAMBDA
#define KOKKOS_LAMBDA [=] __host__ __device__

#define KOKKOS_CLASS_LAMBDA [ =, *this ] __host__ __device__

#else  // !defined(KOKKOS_ENABLE_CUDA_LAMBDA)
#undef KOKKOS_ENABLE_CXX11_DISPATCH_LAMBDA
#endif  // !defined(KOKKOS_ENABLE_CUDA_LAMBDA)

#define KOKKOS_IMPL_FORCEINLINE_FUNCTION __device__ __host__ __forceinline__
#define KOKKOS_IMPL_FORCEINLINE __forceinline__
#define KOKKOS_IMPL_INLINE_FUNCTION __device__ __host__ inline
#define KOKKOS_IMPL_FUNCTION __device__ __host__
#define KOKKOS_IMPL_HOST_FUNCTION __host__
#define KOKKOS_IMPL_DEVICE_FUNCTION __device__

#if defined(KOKKOS_ARCH_KEPLER30)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 30
#elif defined(KOKKOS_ARCH_KEPLER32)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 32
#elif defined(KOKKOS_ARCH_KEPLER35)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 35
#elif defined(KOKKOS_ARCH_KEPLER37)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 37
#elif defined(KOKKOS_ARCH_MAXWELL50)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 50
#elif defined(KOKKOS_ARCH_MAXWELL52)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 52
#elif defined(KOKKOS_ARCH_MAXWELL53)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 53
#elif defined(KOKKOS_ARCH_PASCAL60)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 60
#elif defined(KOKKOS_ARCH_PASCAL61)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 61
#elif defined(KOKKOS_ARCH_VOLTA70)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 70
#elif defined(KOKKOS_ARCH_VOLTA72)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 72
#elif defined(KOKKOS_ARCH_TURING75)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 75
#elif defined(KOKKOS_ARCH_AMPERE80)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 80
#elif defined(KOKKOS_ARCH_AMPERE86)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 86
#elif defined(KOKKOS_ARCH_ADA89)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 89
#elif defined(KOKKOS_ARCH_HOPPER90)
#define KOKKOS_IMPL_ARCH_NVIDIA_GPU 90
#else
#error NVIDIA GPU arch not recognized
#endif

#endif /* KOKKOS_CUDA_SETUP_HPP_ */
