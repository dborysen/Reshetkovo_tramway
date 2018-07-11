#include "Reshetkovo.hpp"

Reshetkovo::Reshetkovo() : 	_dataRows(nullptr),
							_lightsNum(0), _tmpArr(nullptr)
{
	_maxRowAndCol = pow(10,9);
	return ;
}

Reshetkovo::~Reshetkovo()
{
	this->_freeDataList();
	delete [] this->_tmpArr;
	return ;
}

void	Reshetkovo::enterFileName()
{
	// std::cout << "Please enter file name: ";
	// std::getline(std::cin, this->_fileName);

	this->_fileName = "test1-in.txt";
	if (this->_readData() == false || this->_getParameters() == false)
		return ;
	this->_drawTramways();
	return ;
}

bool	Reshetkovo::_getParameters()
{
	char		*tmpStr;
	char		*splitedStr;
	int			data[3];
	int			i = 0;

	i = 0;
	tmpStr = _copyStr(this->_dataRows->data);
	splitedStr = strtok(tmpStr, " ");
	while (splitedStr != nullptr)
	{
		data[i] = atoi(splitedStr);
		splitedStr = strtok(nullptr, " ");
		i++;
	}
	if (data[0] < 1 || data[0] > this->_maxRowAndCol ||
		data[1] < 1 || data[1] > this->_maxRowAndCol ||
		data[2] < 0 || data[2] > 1000)
	{
		std::cout << "ERROR: invalid input data" << std::endl;
		return (false);
	}
	this->_rows = data[0];
	this->_cols = data[1];
	this->_tramwayNum = data[2];
	delete tmpStr;
	return (true);
}

void	Reshetkovo::_fillTmpArrayByZero()
{
	for (int i = 0; i < this->_cols; i++)
	{
		this->_tmpArr[i] = 0;
	}
	return ;
}

void	Reshetkovo::_drawTramways()
{
	this->_tmpArr = new int[this->_cols];
	this->_fillTmpArrayByZero();
	for (int i = 1; i <= this->_rows; i++)
	{
		if (this->_findArrayInFile(i) == false)
		{
			std::cout << "ERROR: invalid input data" << std::endl;
			return;
		}
		this->_countLightsInCurrentRow();
		this->_fillTmpArrayByZero();	
	}
	return ;
}

void	Reshetkovo::_countLightsInCurrentRow()
{
	for (int i = 0; i < this->_cols; i++)
	{
		if (this->_tmpArr[i] == 0)
			this->_lightsNum++;
	}
	return ;
}

int		Reshetkovo::getLightsNum() const
{
	return (this->_lightsNum);
}

bool	Reshetkovo::_findArrayInFile(const int &arrInSearch)
{
	t_inputData	*tmp;
	int			rowNum;

	tmp = this->_dataRows->next;
	rowNum = 0;
	while (tmp != nullptr)
	{
		if (tmp->data != "cheked")
		{
			if (this->_splitStr(tmp->data, arrInSearch) == false)
				return (false);
		}
		tmp = tmp->next;
		rowNum++;
	}
	return (true);
}

bool	Reshetkovo::_splitStr(std::string &str, const int &arrInSearch)
{
	char		*tmpStr;
	char		*splitedStr;
	int			data[3];
	int			i;

	i = 0;
	tmpStr = _copyStr(str);
	splitedStr = strtok(tmpStr, " ");
	while (splitedStr != nullptr)
	{
		data[i] = atoi(splitedStr);
		splitedStr = strtok(nullptr, " ");
		i++;
	}
	if (this->_validation(data) == false)
	{
		delete [] tmpStr;
		return (false);
	}
	if (data[0] == arrInSearch)
	{
		str = "cheked";
		this->_fillTmpArrayByOccupiedCell(data[1] - 1, data[2] - 1);
	}
	delete [] tmpStr;
	return (true);
}

char	*Reshetkovo::_copyStr(const std::string &orig)
{
	char 		*str;
	const char	*origStr;

	origStr = orig.c_str();
	str = new char[orig.length()];
	for (int i = 0; origStr[i] != '\0'; i++)
	{
		str[i] = origStr[i];
	}
	return (str);
}

void	Reshetkovo::_fillTmpArrayByOccupiedCell(int begin, int end)
{
	int length;

	length = end - begin + 1;
	for (int i = 0; i < length; i++)
	{
		this->_tmpArr[begin] = 1;
		begin++;
	}
	return ;
}

void	Reshetkovo::_freeDataList()
{
	t_inputData *tmp;

	while (this->_dataRows != nullptr)
	{
		tmp = this->_dataRows->next;
		delete this->_dataRows;
		this->_dataRows = tmp;
	}
	return ;
}

bool	Reshetkovo::_readData()
{
	std::ifstream 	fin;
	std::string		data;

	fin.open(this->_fileName);
	if (fin.is_open() == 0)
	{
		std::cout << "Error open file" << std::endl;
		return (false);
	}
	while (fin.eof() == 0)
	{
		data = "";
		std::getline(fin, data);
		this->_addNewNode(data);
	}
	fin.close();
	return (true);
}

bool	Reshetkovo::_validation(const int *arr) const
{
	if (this->_isValidFieldParam(arr) == false)
	{
		std::cout << "ERROR: invalid input data" << std::endl;
		return (false);
	}
	return (true);
}

bool	Reshetkovo::_isValidFieldParam(const int *arr) const
{
	for (int i = 0; i < 3; i++)
	{
		if (this->_trainWayValidation(arr[i], i) == false)
			return (false);
	}
	return (true);
}

bool	Reshetkovo::_trainWayValidation(const int &param, const int &typeOfParam) const
{
	if (typeOfParam == BEGIN_COLUMN || typeOfParam == END_COLUMN)
	{
		if (param < 1 || param > this->_cols)
			return (false);
	}
	else if (typeOfParam == ROW_NUM)
	{
		if (param < 1 || param > this->_rows)
			return (false);
	}
	return (true);
}

void	Reshetkovo::_addNewNode(std::string &dataStr)
{
	t_inputData *newNode;
	t_inputData *tmp;

	newNode = new t_inputData;
	newNode->data = dataStr;
	newNode->next = nullptr;
	if (this->_dataRows == nullptr)
		this->_dataRows = newNode;
	else
	{
		tmp = this->_dataRows;
		while (tmp->next != nullptr)
			tmp = tmp->next;
		tmp->next = newNode;
	}
	return ;
}
