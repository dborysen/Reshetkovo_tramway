#ifndef RESHETKOVO_HPP
# define RESHETKOVO_HPP

# define ROWS 					0
# define COLS 					1
# define TRAMWAYNUM 			2
# define ROW_NUM				0
# define BEGIN_COLUMN			1
# define END_COLUMN				2
# define ROWS_COLS_TRAINS		0
# define NUM_OF_NUMBERS_IN_DATA 3

# include <iostream>
# include <string>
# include <fstream>
# include <cmath>

class Reshetkovo
{
	public:
		typedef struct	s_inputData
		{
			std::string			data;
			struct	s_inputData *next;
		}				t_inputData;

		Reshetkovo();
		~Reshetkovo();
		
		void	enterFileName();
		int		getLightsNum() const;

	private:
		std::string		_fileName;
		t_inputData		*_dataRows;
		int				_cols;
		int				_rows;
		int				_tramwayNum;
		int				_lightsNum;
		int				*_tmpArr;
		int				_maxRowAndCol;

		bool			_readData();
		void			_addNewNode(std::string &dataStr);
		void			_freeDataList();
		bool			_validation(const int *arr) const;
		bool			_isValidFieldParam(const int *arr) const;
		bool			_trainWayValidation(const int &param, const int &typeOfParam) const;
		void			_drawTramways();
		void			_fillTmpArrayByZero();
		bool			_findArrayInFile(const int &arrInSearch);
		void			_fillTmpArrayByOccupiedCell(int begin, int end);
		void			_countLightsInCurrentRow();
		char			*_copyStr(const std::string &orig);
		bool			_splitStr(std::string &str, const int &arrInSearch);
		bool			_getParameters();
};

#endif
