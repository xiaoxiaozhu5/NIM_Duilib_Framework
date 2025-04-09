#ifndef UI_CONTROL_NUMBEREDIT_H_
#define UI_CONTROL_NUMBEREDIT_H_

#pragma once

namespace ui 
{

	class UILIB_API NumberEdit : public RichEdit
	{
	public:

	public:
		NumberEdit();
		NumberEdit(const NumberEdit& r) = delete;
		NumberEdit& operator=(const NumberEdit& r) = delete;

		/**
		 * @brief �ж��Ƿ��֧������
		 * @return ���� true ��ʾ��
		 */
		bool IsIntOnly();

		/**
		 * @brief �����Ƿ��֧������
		 * @param[in] bIntOnly Ϊ true ��ֻ������������false Ϊʵ��
		 * @return ��
		 */
		void SetIntOnly(bool bIntOnly = false);

		/**
		 * @brief �ж��Ƿ�������
		 * @return ���� true ��ʾ����
		 */
		bool IsAllowNegative();

		/**
		 * @brief �����Ƿ�������
		 * @param[in] bIntOnly Ϊ true ���������븺��
		 * @return ��
		 */
		void SetAllowNegative(bool bAllowNegative = false);

		/**
 		 * @brief ���ÿؼ����ı�
 		 * @param[in] strText Ҫ���õ��ı�����
 		 * @return ��
 		 */
		virtual void SetText(const std::wstring& strText) override;
		virtual void OnChar(EventArgs& event) override;
		virtual void OnKeyDown(EventArgs& event) override;

		virtual void SetAttribute(const std::wstring& pstrName, const std::wstring& pstrValue) override;

	protected:
		bool m_bIntOnly; //��֧������ Ĭ�Ϸ�
		bool m_bAllowNegative; //������ Ĭ�Ϸ�

	private:
		std::wstring _ToNumberStr(std::wstring str);
	};
	

} // namespace ui

#endif // UI_CONTROL_RICHEDIT_H_
