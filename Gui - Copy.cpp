#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QErrorMessage>
#include <QtWidgets/QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "Gui.h"


GUI::GUI(Service& serv, UserService& userserv, TutValidator& validator1, Repository& repo): service(serv), userService(userserv), validator(validator1), repository(repo)
{
	this->titleWidget = new QLabel(this);
	this->adminButton = new QPushButton(this);
	this->userButton = new QPushButton(this);
	this->initGUI();
	this->connectSignalsAndSlots();

}

void GUI::initGUI()
{
	auto* layout = new QVBoxLayout(this);
	QFont titleFont = this->titleWidget->font();
	this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>Welcome to the Tutorial App! <br> Select your mode!</font></p>");
	titleFont.setItalic(true);
	titleFont.setPointSize(10);
	titleFont.setStyleHint(QFont::System);
	titleFont.setWeight(QFont::Weight(63));
	this->titleWidget->setFont(titleFont);
	layout->addWidget(this->titleWidget);
	this->adminButton->setText("Admin mode");
	layout->addWidget(this->adminButton);
	this->userButton->setText("User mode");
	layout->addWidget(this->userButton);
	this->setLayout(layout);
	this->setStyleSheet("background-color:#D9DBF1");

}

GUI::~GUI()
{

}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);

}

void GUI::showAdmin()
{
	auto* admin = new AdminGUI(this, this->service, this->validator, this->repository);
	admin->show();

}

AdminGUI::AdminGUI(QWidget* parent, Service& serv, TutValidator& val, Repository& repo) : service(serv), validator(val), repository(repo)
{
	this->titleWidget = new QLabel(this);
	this->tutorialsListWidget = new QListWidget();

	this->titleLineEdit = new QLineEdit();
	this->presenterLineEdit = new QLineEdit();
	this->minutesLineEdit = new QLineEdit();
	this->secondsLineEdit = new QLineEdit();
	this->likesLineEdit = new QLineEdit();
	this->sourceLineEdit = new QLineEdit();

	this->addButton = new QPushButton("Add");
	this->deleteButton = new QPushButton("Delete");
	this->updateButton = new QPushButton("Update");
	this->chartButton = new QPushButton("Display chart");
	setParent(parent);
	setWindowFlag(Qt::Window);
	this->initAdminGUI();
	this->populateList();
	this->connectSignalsAndSlots();

	//this->listModel = new TutorialListModel(this->repository);
}


void AdminGUI::initAdminGUI()
{
	auto* layout = new QVBoxLayout(this);
	QFont titleFont = this->titleWidget->font();

	this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>ADMIN MODE</font></p>");
	titleFont.setItalic(true);
	titleFont.setPointSize(10);
	titleFont.setStyleHint(QFont::System);
	titleFont.setWeight(QFont::Weight(63));
	this->titleWidget->setFont(titleFont);
	layout->addWidget(this->titleWidget);

	layout->addWidget(this->tutorialsListWidget);

	auto* tutDetailsLayout = new QFormLayout();
	tutDetailsLayout->addRow("Title", this->titleLineEdit);
	tutDetailsLayout->addRow("Presenter", this->presenterLineEdit);
	tutDetailsLayout->addRow("Minutes", this->minutesLineEdit);
	tutDetailsLayout->addRow("Seconds", this->secondsLineEdit);
	tutDetailsLayout->addRow("Likes", this->likesLineEdit);
	tutDetailsLayout->addRow("Source", this->sourceLineEdit);
	layout->addLayout(tutDetailsLayout);

	auto* buttonsLayout = new QGridLayout();
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);
	buttonsLayout->addWidget(this->updateButton, 1, 0);
	buttonsLayout->addWidget(this->chartButton, 1, 1);
	layout->addLayout(buttonsLayout);
}

void AdminGUI::populateList()
{
	this->tutorialsListWidget->clear();
	std::vector<Tutorial> allTutorials = this->service.GetServ();
	for (Tutorial& tut : allTutorials)
		this->tutorialsListWidget->addItem(QString::fromStdString(tut.GetTitle()));
}

void AdminGUI::connectSignalsAndSlots()
{
	QObject::connect(this->tutorialsListWidget, &QListWidget::itemSelectionChanged, [this]()
		{
			int selectedIndex = this->getSelectedIndex();
			if (selectedIndex < 0)
				return;
			Tutorial tut = this->service.GetServ()[selectedIndex];
			this->titleLineEdit->setText(QString::fromStdString(tut.GetTitle()));
			this->presenterLineEdit->setText(QString::fromStdString(tut.GetPresenter()));
			this->minutesLineEdit->setText(QString::fromStdString(std::to_string(tut.GetMinutes())));
			this->secondsLineEdit->setText(QString::fromStdString(std::to_string(tut.GetSeconds())));
			this->likesLineEdit->setText(QString::fromStdString(std::to_string(tut.GetLikes())));
			this->sourceLineEdit->setText(QString::fromStdString(tut.GetSource()));

		});
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addTutorial);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteTutorial);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateTutorial);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);

}

void AdminGUI::addTutorial()
{
	std::string title = this->titleLineEdit->text().toStdString();
	std::string presenter = this->presenterLineEdit->text().toStdString();
	std::string minutes_s = this->minutesLineEdit->text().toStdString();
	std::string seconds_s = this->secondsLineEdit->text().toStdString();
	std::string likes_s = this->likesLineEdit->text().toStdString();
	std::string source = this->sourceLineEdit->text().toStdString();

	int min, sec, likes;
	try
	{
		this->validator.validateTitle(title);
		this->validator.validatePresenter(presenter);
		this->validator.validateMinStr(minutes_s);
		min = stoi(minutes_s);
		this->validator.validateMinutes(min);
		this->validator.validateSecStr(seconds_s);
		sec = stoi(seconds_s);
		this->validator.validateSeconds(sec);
		this->validator.validateLikesStr(likes_s);
		likes = stoi(likes_s);
		this->validator.validateSource(source);
		this->service.AddTutorialService(title, presenter, min, sec, likes, source);
		this->populateList();

	}
	catch (ValidationException& exc)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(exc.what());
		error->setWindowTitle("Invalid input!");
		error->exec();

	}
	catch (RepositoryException& re)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(re.what());
		error->setWindowTitle("Error at adding tutorial!");
		error->exec();
	}
}


void AdminGUI::deleteTutorial()
{
	std::string title = this->titleLineEdit->text().toStdString();
	std::string presenter = this->presenterLineEdit->text().toStdString();
	std::string minutes_s = this->minutesLineEdit->text().toStdString();
	std::string seconds_s = this->secondsLineEdit->text().toStdString();
	std::string likes_s = this->likesLineEdit->text().toStdString();
	std::string source = this->sourceLineEdit->text().toStdString();

	int min, sec, likes;
	try
	{
		this->validator.validateTitle(title);
		this->validator.validatePresenter(presenter);
		this->validator.validateMinStr(minutes_s);
		min = stoi(minutes_s);
		this->validator.validateMinutes(min);
		this->validator.validateSecStr(seconds_s);
		sec = stoi(seconds_s);
		this->validator.validateSeconds(sec);
		this->validator.validateLikesStr(likes_s);
		likes = stoi(likes_s);
		this->validator.validateSource(source);
		this->service.DeleteTutorialService(title, presenter, min, sec, likes, source);
		this->populateList();

	}
	catch (ValidationException& exc)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(exc.what());
		error->setWindowTitle("Invalid input!");
		error->exec();

	}
	catch (RepositoryException& re)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(re.what());
		error->setWindowTitle("Error at adding tutorial!");
		error->exec();
	}
}

void AdminGUI::updateTutorial()
{
	int index = this->getSelectedIndex();
	try
	{
		if (index < 0)
		{
			auto* error = new QMessageBox();
			error->setIcon(QMessageBox::Critical);
			error->setText("No tutorial selected!");
			error->setWindowTitle("Selection error!");
			error->exec();
		}
		else
		{
			Tutorial& tut = this->service.GetServ()[index];
			std::string new_title = this->titleLineEdit->text().toStdString();
			std::string new_presenter = this->presenterLineEdit->text().toStdString();
			std::string new_minutes_s = this->minutesLineEdit->text().toStdString();
			int n_min, n_sec, n_likes;
			std::string new_seconds_s = this->secondsLineEdit->text().toStdString();
			std::string new_likes_s = this->likesLineEdit->text().toStdString();
			std::string new_source = this->sourceLineEdit->text().toStdString();

			this->validator.validateTitle(new_title);
			this->validator.validatePresenter(new_presenter);
			this->validator.validateMinStr(new_minutes_s);
			n_min = stoi(new_minutes_s);
			this->validator.validateMinutes(n_min);
			this->validator.validateSecStr(new_seconds_s);
			n_sec = stoi(new_seconds_s);
			this->validator.validateSeconds(n_sec);
			this->validator.validateLikesStr(new_likes_s);
			n_likes = stoi(new_likes_s);

			this->validator.validateSource(new_source);
			std::string o_title = tut.GetTitle();
			std::string o_pres = tut.GetPresenter();
			int o_min = tut.GetMinutes();
			int o_sec = tut.GetSeconds();
			int o_likes = tut.GetLikes();
			std::string o_source = tut.GetSource();

			this->service.UpdateTutorialService(o_title, o_pres, o_min, o_sec, o_likes, o_source, new_title, new_presenter, n_min, n_sec, n_likes, new_source);
			this->populateList();
		}

	}
	catch (ValidationException& exc)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(exc.what());
		error->setWindowTitle("Invalid input!");
		error->exec();
	}
	catch (RepositoryException& re)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(re.what());
		error->setWindowTitle("Error at adding tutorial!");
		error->exec();
	}
}

void AdminGUI::displayChart()
{
	//todo
}


int AdminGUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->tutorialsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty())
	{
		this->titleLineEdit->clear();
		this->presenterLineEdit->clear();
		this->minutesLineEdit->clear();
		this->secondsLineEdit->clear();
		this->likesLineEdit->clear();
		this->sourceLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

AdminGUI::~AdminGUI()
{

}

void GUI::showUser()
{
	auto* user = new UserGUI(this, this->service, this->userService, this->validator);
	user->show();
}



UserGUI::UserGUI(QWidget* parent, Service& serv, UserService& userserv, TutValidator& valid) : service(serv), userService(userserv), validator(valid)
{
	this->titleWidget = new QLabel(this);
	this->tutorialsLisWidget = new QListWidget();
	this->watchListWidget = new QListWidget();
	this->titleLineEdit = new QLineEdit();
	this->presenterLineEdit = new QLineEdit();
	this->minutesLineEdit = new QLineEdit();
	this->secondsLineEdit = new QLineEdit();
	this->likesLineEdit = new QLineEdit();
	this->sourceLineEdit = new QLineEdit();
	this->filterPresenterLineEdit = new QLineEdit();
	this->tutGivenPresenterButton = new QPushButton("Add to the watch list");
	this->deleteTutWLButton = new QPushButton("Watched this tutorial");
	this->seeListButton = new QPushButton("See list");
	this->filterButton = new QPushButton("Filter");
	this->csvButton = new QRadioButton("CSV");
	this->htmlButton = new QRadioButton("HTML");
	this->repoTypeSelected = false;
	this->filtered = false;
	setParent(parent);
	setWindowFlag(Qt::Window);
	this->initUserGUI();
	this->populateTutorialsList();
	this->connectSignalsAndSlots();

	this->nextButton = new QPushButton("Next tutorial");
	this->saveButton = new QPushButton("Save");
	this->openButton = new QPushButton("Open");
	this->deleteButton = new QPushButton("Delete from watchList");
	this->showButton = new QPushButton("Show");
	
}

void UserGUI::initUserGUI()
{
	auto* layout = new QVBoxLayout(this);
	QFont titleFont = this->titleWidget->font();
	this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>USER MODE <br> Select the type of file you want for saving your adopted dogs!</font></p>");
	titleFont.setItalic(true);
	titleFont.setPointSize(10);
	titleFont.setStyleHint(QFont::System);
	titleFont.setWeight(QFont::Weight(63));
	this->titleWidget->setFont(titleFont);
	layout->addWidget(this->titleWidget);

	auto* radioButtonLayout = new QGridLayout(this);
	radioButtonLayout->addWidget(this->csvButton, 0, 0);
	radioButtonLayout->addWidget(this->htmlButton, 1, 0);
	radioButtonLayout->addWidget(this->seeListButton, 0, 1);
	layout->addLayout(radioButtonLayout);

	auto* listLayout = new QGridLayout(this);
	listLayout->addWidget(this->tutorialsLisWidget, 0, 0);
	listLayout->addWidget(this->watchListWidget, 0, 1);
	layout->addLayout(listLayout);

	
	auto* tutDetailsLayout = new QFormLayout();
	tutDetailsLayout->addRow("Title", this->titleLineEdit);
	tutDetailsLayout->addRow("Presenter", this->presenterLineEdit);
	tutDetailsLayout->addRow("Minutes", this->minutesLineEdit);
	tutDetailsLayout->addRow("Seconds", this->secondsLineEdit);
	tutDetailsLayout->addRow("Likes", this->likesLineEdit);
	tutDetailsLayout->addRow("Source", this->sourceLineEdit);
	tutDetailsLayout->addRow(this->tutGivenPresenterButton);

	layout->addLayout(tutDetailsLayout);

	
	auto* filterPresenter = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available tutorials by presenter</font></p>");
	QFont filterFont = filterPresenter->font();
	filterFont.setPointSize(10);
	filterFont.setStyleHint(QFont::System);
	filterFont.setWeight(QFont::Weight(63));
	filterPresenter->setFont(filterFont);
	layout->addWidget(filterPresenter);


	auto* filterDetailsLayout = new QFormLayout();
	filterDetailsLayout->addRow("Presenter", this->filterPresenterLineEdit);
	filterDetailsLayout->addRow(this->filterButton);
	layout->addLayout(filterDetailsLayout);


}

void UserGUI::populateTutorialsList()
{
	this->tutorialsLisWidget->clear();
	std::vector<Tutorial> allTutorials = this->service.GetServ();
	for (Tutorial& tut : allTutorials)
		this->tutorialsLisWidget->addItem(QString::fromStdString(tut.GetTitle()));

}

void UserGUI::connectSignalsAndSlots()
{
	
	QObject::connect(this->tutorialsLisWidget, &QListWidget::itemClicked, [this]()
		{
			std::string tut_title = this->tutorialsLisWidget->selectedItems().at(0)->text().toStdString();
			int index = this->service.FindbyTitle(tut_title);
			Tutorial tutorial = this->service.GetServ()[index];
			this->titleLineEdit->setText(QString::fromStdString(tutorial.GetTitle()));
			this->presenterLineEdit->setText(QString::fromStdString(tutorial.GetPresenter()));
			this->minutesLineEdit->setText(QString::fromStdString(std::to_string(tutorial.GetMinutes())));
			this->secondsLineEdit->setText(QString::fromStdString(std::to_string(tutorial.GetSeconds())));
			this->likesLineEdit->setText(QString::fromStdString(std::to_string(tutorial.GetLikes())));
			this->sourceLineEdit->setText(QString::fromStdString(tutorial.GetSource()));
			std::string source = std::string("start ").append(tutorial.GetSource());
			system(source.c_str());
		});

	QObject::connect(this->csvButton, &QRadioButton::clicked, [this]() {
		this->userService.repoType("csv");
		this->repoTypeSelected = true;
		});

	QObject::connect(this->htmlButton, &QPushButton::clicked, [this]() {
		this->userService.repoType("html");
		this->repoTypeSelected = true;

		});

	QObject::connect(this->seeListButton, &QPushButton::clicked, [this]()
		{
			if (!this->repoTypeSelected)
			{
				auto* error = new QMessageBox();
				error->setIcon(QMessageBox::Warning);
				error->setText("Please select the type of file you want!");
				error->setWindowTitle("File type warning!");
				error->exec();
			}
			else {
				std::string source = std::string("start ").append(this->userService.getFileService());
				//std::string source = this->userService.getFileService();
				//ShellExecute(NULL, "open", "source", NULL, NULL, SW_SHOWNORMAL);
				//ShellExecute(NULL, "open", "D:\\FACULTATE\\Materiale facultate 2021-2022\\1.2\\Object Oriented Programming\\Assignments\\A8-9\\A8-9\\A8-9\\WatchList.csv", NULL, NULL, SW_SHOWNORMAL);

				system(source.c_str());
			}
		});
	QObject::connect(this->tutGivenPresenterButton, &QPushButton::clicked, this, &UserGUI::addTutorial);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterTutorials);
	//QObject::connect(this->nextButton, &QPushButton::clicked, this, UserGUI::userNext);
	//QObject::connect(this->deleteButton, &QPushButton::clicked, this, UserGUI::userDelete);
}

void UserGUI::userNext()
{
	
}

void UserGUI::userDelete()
{
	if (this->watchListWidget->selectedItems().size() != 0)
	{
		QListWidgetItem* tutorial = this->watchListWidget->takeItem(this->getSelectedIndex() + 1);

	}
}

int UserGUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->tutorialsLisWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty())
	{
		this->titleLineEdit->clear();
		this->presenterLineEdit->clear();
		this->minutesLineEdit->clear();
		this->secondsLineEdit->clear();
		this->likesLineEdit->clear();
		this->sourceLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}


void UserGUI::populateWatchList()
{
	this->watchListWidget->clear();
	std::vector<Tutorial> allTutorials = this->userService.getAllUserService();
	for (Tutorial& tut : allTutorials)
		this->watchListWidget->addItem(QString::fromStdString(tut.GetTitle()));
}

void UserGUI::addTutorial()
{
	if (!this->repoTypeSelected)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Warning);
		error->setText("Please select the type of file you want!");
		error->setWindowTitle("File type warning!");
		error->exec();
	}
	else
	{
		QMessageBox::StandardButton reply = QMessageBox::question(this, "Tutorial", "Want to add tutorial? ", QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			std::string title = this->titleLineEdit->text().toStdString();
			std::string presenter = this->presenterLineEdit->text().toStdString();
			std::string s_minutes = this->minutesLineEdit->text().toStdString();
			std::string s_seconds = this->secondsLineEdit->text().toStdString();
			std::string s_likes = this->likesLineEdit->text().toStdString();
			std::string s_source = this->sourceLineEdit->text().toStdString();
			int min, sec, likes;
			try
			{
				this->validator.validateTitle(title);
				this->validator.validatePresenter(presenter);
				this->validator.validateMinStr(s_minutes);
				min = stoi(s_minutes);
				this->validator.validateMinutes(min);
				this->validator.validateSecStr(s_seconds);
				sec = stoi(s_seconds);
				this->validator.validateSeconds(sec);
				this->validator.validateLikesStr(s_likes);
				likes = stoi(s_likes);
				this->validator.validateSource(s_source);
				Tutorial tut = Tutorial(title, presenter, min, sec, likes, s_source);
				this->userService.AddUserService(tut);
				if (!this->filtered)
					this->populateTutorialsList();
				else
					this->watchListWidget->addItem(this->tutorialsLisWidget->takeItem(this->getSelectedIndex()));
				this->populateWatchList();

			}
			catch (ValidationException& exc)
			{
				auto* error = new QMessageBox();
				error->setIcon(QMessageBox::Critical);
				error->setText(exc.what());
				error->setWindowTitle("Invalid input!");
				error->exec();
			}
			catch (RepositoryException& re)
			{
				auto* error = new QMessageBox();
				error->setIcon(QMessageBox::Critical);
				error->setText(re.what());
				error->setWindowTitle("Error at adding dog!");
				error->exec();
			}
		}
		
	}
}
	

void UserGUI::filterTutorials()
{
	try
	{
		std::string presenter_filter = this->presenterLineEdit->text().toStdString();
		if (presenter_filter.empty())
		{
			this->filtered = false;
			this->populateTutorialsList();
		}
		else
		{
			this->validator.validateString(presenter_filter);
			std::vector<Tutorial> validTutorials;
			this->service.getFiltered(validTutorials, presenter_filter);
			if (validTutorials.empty())
			{
				std::string error;
				error += std::string("The list of valid tutorials is empty!");
				if (!error.empty())
					throw WLException(error);
				
			}
			else
			{
				this->filtered = true;
				this->tutorialsLisWidget->clear();
				for (Tutorial& tut : validTutorials)
					this->tutorialsLisWidget->addItem(QString::fromStdString(tut.GetTitle()));
			}
			

		}
	}
	catch (ValidationException& ve)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(ve.what());
		error->setWindowTitle("Validation error!");
		error->exec();
	}
	catch (WLException& ue) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(ue.what());
		error->setWindowTitle("Filter error!");
		error->exec();
	}
	
}
	
UserGUI::~UserGUI()
{

}

int TutorialListModel::rowCount(const QModelIndex &parent) const
{
	return this->repo.GetTutorials().size();
}

QVariant TutorialListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	Tutorial currentTutorial = this->repo.GetTutorials()[row];
	if (role == Qt::DisplayRole)
		return QString::fromStdString(currentTutorial.GetTitle());
	return QVariant();
}



