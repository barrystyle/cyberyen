#include <wallet/reserve.h>
#include <wallet/scriptpubkeyman.h>
#include <wallet/wallet.h>

void ReserveDestination::KeepDestination()
{
    if (nIndex != -1) {
	m_spk_man->KeepDestination(nIndex, type);
    }
    nIndex = -1;
    address = CNoDestination();
}

void ReserveDestination::ReturnDestination()
{
    if (nIndex != -1) {
	KeyPurpose purpose = (type == OutputType::MWEB) ? KeyPurpose::MWEB : (fInternal ? KeyPurpose::INTERNAL : KeyPurpose::EXTERNAL);
	m_spk_man->ReturnDestination(nIndex, purpose, address);
    }
    nIndex = -1;
    address = CNoDestination();
}

bool ReserveDestination::GetReservedDestination(CTxDestination& dest, bool internal)
{
    m_spk_man = pwallet->GetScriptPubKeyMan(type, internal);
    if (!m_spk_man) {
	printf("Error: No %s addresses available.", FormatOutputType(type).c_str());
	return false;
    }


    if (nIndex == -1)
    {
	m_spk_man->TopUp();

	CKeyPool keypool;
	if (!m_spk_man->GetReservedDestination(type, internal, address, nIndex, keypool)) {
	    return false;
	}
	fInternal = keypool.fInternal;
    }
    dest = address;
    return true;
}
