
#include "LinearMap.h"

namespace VS
{
    void swap(std::vector<std::vector<double>> mat, int row1, int row2, int col);
    int rankOfMatrix(std::vector<std::vector<double>> mat, int rows, int columns);

	int LinearMap::CalculateRank()
	{
        Matrix M2 = M.transpose();
		std::vector<std::vector<double>> vect_vect = M2.convert_to_std_vect();
        return rankOfMatrix(vect_vect, M2.rows, M2.columns);
	}

    // source: https://www.geeksforgeeks.org/program-for-rank-of-matrix/

    /* function for finding rank of matrix */
    int rankOfMatrix(std::vector<std::vector<double>> mat, int rows, int columns)
    {
        int rank = columns;

        for (int row = 0; row < rank; row++)
        {
            // Before we visit current row 'row', we make
            // sure that mat[row][0],....mat[row][row-1]
            // are 0.

            // Diagonal element is not zero
            if (mat[row][row])
            {
                for (int col = 0; col < rows; col++)
                {
                    if (col != row)
                    {
                        // This makes all entries of current
                        // column as 0 except entry 'mat[row][row]'
                        double mult = (double)mat[col][row] /
                            mat[row][row];
                        for (int i = 0; i < rank; i++)
                            mat[col][i] -= mult * mat[row][i];
                    }
                }
            }

            // Diagonal element is already zero. Two cases
            // arise:
            // 1) If there is a row below it with non-zero
            //    entry, then swap this row with that row
            //    and process that row
            // 2) If all elements in current column below
            //    mat[r][row] are 0, then remvoe this column
            //    by swapping it with last column and
            //    reducing number of columns by 1.
            else
            {
                bool reduce = true;

                /* Find the non-zero element in current
                    column  */
                for (int i = row + 1; i < rows; i++)
                {
                    // Swap the row with non-zero element
                    // with this row.
                    if (!VS::Matrix::IsZero(mat[i][row]))
                    {
                        swap(mat, row, i, rank);
                        reduce = false;
                        break;
                    }
                }

                // If we did not find any row with non-zero
                // element in current columnm, then all
                // values in this column are 0.
                if (reduce)
                {
                    // Reduce number of columns
                    rank--;

                    // Copy the last column here
                    for (int i = 0; i < rows; i++)
                        mat[i][row] = mat[i][rank];
                }

                // Process this row again
                row--;
            }
        }
        return rank;
    }

    void swap(std::vector<std::vector<double>> mat, int row1, int row2, int col)
    {
        for (int i = 0; i < col; i++)
        {
            double temp = mat[row1][i];
            mat[row1][i] = mat[row2][i];
            mat[row2][i] = temp;
        }
    }
}
