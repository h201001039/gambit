//
// FILE: nfgconv.cc -- Convert between types of normal forms
//
// $Id$
//


#include "nfg.h"
#include "nfplayer.h"
#include "nfstrat.h"
#include "nfgciter.h"
#include "rational.h"

Nfg<gRational> *ConvertNfg(const Nfg<double> &orig)
{
  Nfg<gRational> *N = new Nfg<gRational>(orig.NumStrats());
  
  N->SetTitle(orig.GetTitle());

  for (int pl = 1; pl <= N->NumPlayers(); pl++)  {
    NFPlayer *p1 = orig.Players()[pl];
    NFPlayer *p2 = N->Players()[pl];

    p2->SetName(p1->GetName());
    
    for (int st = 1; st <= p2->NumStrats(); st++)
      p2->Strategies()[st]->name = p1->Strategies()[st]->name;
  }
  
  for (int outc = 1; outc <= orig.NumOutcomes(); outc++)  {
    NFOutcome<gRational> *outcome = 
      (outc > 1) ? N->NewOutcome() : N->Outcomes()[1];

    for (int pl = 1; pl <= N->NumPlayers(); pl++)
      (*outcome)[pl] = gRational((*orig.Outcomes()[outc])[pl]);
  }
		       
  NFSupport S1(orig);
  NFSupport S2(*N);

  NfgContIter<double> C1(S1);
  NfgContIter<gRational> C2(S2);
  
  do   {
    C2.SetOutcome(N->Outcomes()[C1.GetOutcome()->GetNumber()]);

    C2.NextContingency();
  } while (C1.NextContingency());

  return N;
}



Nfg<double> *ConvertNfg(const Nfg<gRational> &orig)
{
  Nfg<double> *N = new Nfg<double>(orig.NumStrats());
  
  N->SetTitle(orig.GetTitle());

  for (int pl = 1; pl <= N->NumPlayers(); pl++)  {
    NFPlayer *p1 = orig.Players()[pl];
    NFPlayer *p2 = N->Players()[pl];

    p2->SetName(p1->GetName());
    
    for (int st = 1; st <= p2->NumStrats(); st++)
      p2->Strategies()[st]->name = p1->Strategies()[st]->name;
  }

  for (int outc = 1; outc <= orig.NumOutcomes(); outc++)  {
    NFOutcome<double> *outcome = 
      (outc > 1) ? N->NewOutcome() : N->Outcomes()[1];

    for (int pl = 1; pl <= N->NumPlayers(); pl++)
      (*outcome)[pl] = (double) (*orig.Outcomes()[outc])[pl];
  }
		       
  NFSupport S1(orig);
  NFSupport S2(*N);

  NfgContIter<gRational> C1(S1);
  NfgContIter<double> C2(S2);
  
  do   {
    C2.SetOutcome(N->Outcomes()[C1.GetOutcome()->GetNumber()]);

    C2.NextContingency();
  } while (C1.NextContingency());

  return N;
}



