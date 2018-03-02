// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xc1;
        vAlertPubKey = ParseHex("04c9bcf0bc5016b8b73f59d05d235aae3199356d0b1dcb1f11134c16eec1f91cfb5289f78fb70e5a5dbc86284797a7975fac4540a73647864b3a9ba194ef889975");
        nDefaultPort = 45130;
        nRPCPort = 45131;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "09 Feb 2018 - Russia's Largest Bank Caught Employees Mining For Crypto";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = 0;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1518821950, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1518821950; // Mon, 01 May 2017 00:00:00 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 23874616;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 144b5ad15014270780e2d349c7ed1c410aa07730e689cb6edb99da90bb4e880e
        block.nTime = 1518821950
        block.nNonce = 23874616
        block.GetHash = ab65127257a9f05c43cc08f074a06d6948387f8b2a6cd2eccd906055e60ec5ee
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xab65127257a9f05c43cc08f074a06d6948387f8b2a6cd2eccd906055e60ec5ee"));
        assert(genesis.hashMerkleRoot == uint256("0x144b5ad15014270780e2d349c7ed1c410aa07730e689cb6edb99da90bb4e880e"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,57);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,55);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,59);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("seed1.arioncoin.com",  "seed1.arioncoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2.arioncoin.com",  "seed2.arioncoin.com"));
        vSeeds.push_back(CDNSSeedData("seed3.arioncoin.com",  "seed3.arioncoin.com"));
        vSeeds.push_back(CDNSSeedData("seed4.arioncoin.com",  "seed4.arioncoin.com"));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "AQrdxgSckxugGue85kbKsikqvyotAXp211";

        strBudgetAddress = "ATVAXA6LU2ewsXrsW5aXhoF9NKFT4x2kun";
        fBudgetPercentage = 1;

        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 0;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xde;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xaa;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04ac24ab003c828cdd9cf4db2ebbde8e1cecb3bbfa8b3127fcb9dd9b84d44112080827ed7c49a648af9fe788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 25130;
        nRPCPort = 25131;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1518821950+30;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 691387;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 144b5ad15014270780e2d349c7ed1c410aa07730e689cb6edb99da90bb4e880e
        block.nTime = 1518821950+30
        block.nNonce = 691387
        block.GetHash = 635672f6f669c37759ce35bf13d3bc0d36169abca1819f55446088a79693ff78
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x635672f6f669c37759ce35bf13d3bc0d36169abca1819f55446088a79693ff78"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,39);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,63);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,37);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0xee;
        pchMessageStart[3] = 0x67;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1518821950+90;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 293264;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10300;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 649cdbbabfae8f7d67fef579d2df8968025727fef9a30d961f7d72e84f8a01c9
        block.nTime = 1518821950+90
        block.nNonce = 293264
        block.GetHash = b2001372d8331a8badd91720aa3c6c7c700641aa4fe918fb092d4f19db1cbac2
        */

        assert(hashGenesisBlock == uint256("0xb2001372d8331a8badd91720aa3c6c7c700641aa4fe918fb092d4f19db1cbac2"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
