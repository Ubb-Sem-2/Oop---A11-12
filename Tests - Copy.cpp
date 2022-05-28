
/*
#include "Tests.h"
//#include "Tutorial.h"
#include <assert.h>
//#include "Repository.h"
#include "Service.h"
//#include "WatchList.h"

using namespace std;

void Tests::test_GetTitle()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetTitle() == "as");

}



void Tests::test_GetPresenter()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetPresenter() == "de");
}

void Tests::test_GetMinutes()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetMinutes() == 12);
}



void Tests::test_GetSeconds()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetSeconds() == 23);
}

void Tests::test_GetLikes()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetLikes() == 100);
}

void Tests::test_GetSource()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	assert(t.GetSource() == "dwjnd");
}


void Tests::test_SetTitle()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetTitle("mare");
	assert(t.GetTitle()=="mare");
}


void Tests::test_SetPresenter()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetPresenter("pres");
	assert(t.GetPresenter() == "pres");

}

void Tests::test_SetMinutes()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetMinutes(10);
	assert(t.GetMinutes() == 10);


}

void Tests::test_SetSeconds()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetSeconds(29);
	assert(t.GetSeconds() == 29);

}

void Tests::test_SetLikes()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetLikes(50);
	assert(t.GetLikes() == 50);
}


void Tests::test_SetSource()
{
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	t.SetSource("anaana");
	assert(t.GetSource() == "anaana");
}


void Tests::TutorialTests()
{
	test_GetTitle();
	test_GetPresenter();
	test_GetMinutes();
	test_GetSeconds();
	test_GetLikes();
	test_GetSource();
	test_SetTitle();
	test_SetPresenter();
	test_SetMinutes();
	test_SetSeconds();
	test_SetLikes();
	test_SetSource();

}


void Tests::test_AddTutorial()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	repo.AddTutorial(t);
	assert(repo.GetLength() == 1);

}



void Tests::test_DeleteTutorial()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	repo.AddTutorial(t);
	assert(repo.GetLength() == 1);

	repo.DeleteTutorial(1);
	assert(repo.GetLength() == 0);

}


void Tests::test_GetLength()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	repo.AddTutorial(t);
	int i = repo.GetLength();
	assert(i == 1);

}


void Tests::test_GetTutorials()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	repo.AddTutorial(t);

	Tutorial* t1 = repo.GetTutorials();
	assert(*t1 == t);

}


void Tests::test_CheckIfExist()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	Tutorial t1("aas", "dde", 12, 23, 100, "dwjdscnd");
	repo.AddTutorial(t);
	assert(repo.CheckIfExist(t) == 0);
	assert(repo.CheckIfExist(t1) == -1);

}

void Tests::test_UpdateTutorial()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	Tutorial t("as", "de", 12, 23, 100, "dwjnd");
	Tutorial t1("aas", "dde", 12, 23, 100, "dwjdscnd");
	repo.AddTutorial(t);
	assert(repo.UpdateTutorial(0, t) == 1);
	assert(repo.UpdateTutorial(1, t1) == -1);


}


void Tests::test_RepositoryAll()
{
	test_AddTutorial();
	test_DeleteTutorial();
	test_GetLength();
	test_GetTutorials();
	test_CheckIfExist();
	test_UpdateTutorial();
}




void Tests::TestAddTutServ()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);

	int res = serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	assert(res == 1);

	int r = serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	assert(r == -1);

}


void Tests::TestDeleteTutServ()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	int res = serv.DeleteTutorialService("Aass", "aad", 12, 23, 144, "iond");
	assert( res == 1);
	int r1 = serv.DeleteTutorialService("akml", "ad", 11, 23, 334, "klw");
	assert(r1 == -1);

}

void Tests::TestUpdateTutServ()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");

	int r1 = serv.UpdateTutorialService("A", "add", 102, 233, 1044, "ionda", "sd", "kk", 44, 45, 100, "opl");
	assert(r1 == -1);

	int res = serv.UpdateTutorialService("Aass", "aad", 12, 23, 144, "iond", "sd", "kk", 44, 45, 100, "opl");
	assert(res == 1);



}

void Tests::TestGetTutorialRepo()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	Tutorial* tut = serv.GetTutorialRepo();
	assert(*tut == t);

}

void Tests::TestGetLenRepo()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	int len = serv.GetLengthRepo();
	assert(len ==1);

}


void Tests::TestAddtoWl()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	//serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	serv.AddToWL(t);

	assert(serv.GetLenWL() ==1);

	Tutorial t1("Adss", "add", 112, 213, 1414, "iodsdnd");
	serv.AddToWL(t1);
	assert(serv.GetLenWL() == 2);

}


void Tests::TestGetTutWL()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);

	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	serv.AddToWL(t);
	Tutorial* tutorials= serv.GetTutorialsWL();
	assert(*tutorials == t);
}


void Tests::TestGetLenWL()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);

	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	serv.AddToWL(t);
	assert(serv.GetLenWL() ==1);
}


void Tests::TestDeleteTutWL()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);

	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	serv.AddToWL(t);
	serv.DeleteTutorialWL(0);
	assert(serv.GetLenWL() == 0);

}

void Tests::TestFindInRepo()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);

	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	Tutorial t1("Adss", "add", 112, 213, 1414, "iodsdnd");
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	serv.AddToWL(t);
	Tutorial * tut = serv.GetTutorialsWL();
	assert(*tut == t);
	int res = serv.FindInRepo(t);
	assert(res == 0);
	int res1 = serv.FindInRepo(t1);
	assert(res1==-1);

}



void Tests::TestIncreaseLike()
{
	DynamicVector<Tutorial> vect;
	Repository repo(vect);
	WatchList watch(vect);
	Service serv(repo, watch);
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	Tutorial tut("Adss", "add", 112, 213, 1414, "iodsdnd");
	serv.AddTutorialService("Aass", "aad", 12, 23, 144, "iond");
	serv.AddTutorialService("Adss", "add", 112, 213, 1414, "iodsdnd");
	serv.IcreaseLikes(0);
	int likes = t.GetLikes() + 1;
	assert(likes ==145);

	serv.IcreaseLikes(1);
	int lik = tut.GetLikes() + 1;
	assert(lik == 1415);


}

void Tests::TestServiceALL()
{

	TestAddTutServ();
	TestDeleteTutServ();
	TestUpdateTutServ();
	TestGetTutorialRepo();
	TestGetLenRepo();
	TestAddtoWl();
	TestGetTutWL();
	TestGetLenWL();
	TestDeleteTutWL();
	TestFindInRepo();
	TestIncreaseLike();
}

void Tests::TestaddDA()
{

	DynamicVector<Tutorial> da;
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	Tutorial tut("Adss", "add", 112, 213, 1414, "iodsdnd");

	da.add(t);
	assert(da.GetLength() == 1);

	da.add(tut);
	assert(da.GetLength() == 2);


}


void Tests::TestdeleteDA()
{
	DynamicVector<Tutorial> da;
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	Tutorial tut("Adss", "add", 112, 213, 1414, "iodsdnd");

	da.add(t);

	da.add(tut);
	da.Delete(0);
	assert(da.GetLength() ==1);


}

void Tests::TestResizeDA()
{
	DynamicVector<Tutorial> da;
	Tutorial t("Aass", "aad", 12, 23, 144, "iond");
	da.add(t);
	da.resize();
	//assert(da.capacity == 20);



}

void Tests::TestDAALL()
{
	TestaddDA();
	TestdeleteDA();
	TestResizeDA();
}

void Tests::TestAll()
{
	TutorialTests();
	test_RepositoryAll();
	TestServiceALL();
	TestDAALL();

}
*/