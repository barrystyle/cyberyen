// Copyright (c) 2019-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <node/context.h>

#include <banman.h>
#include <interfaces/chain.h>
#include <net.h>
#include <net_processing.h>
#include <scheduler.h>
#include <txmempool.h>

namespace node {
NodeContext::NodeContext() = default;
NodeContext::~NodeContext() = default;
}
